#include "Model.h"
#include "assimp.h"
#include "Math/IndexedTriangleList.h"
#include "Drawables/Drawable.h"
#include "Drawables/PhongDrawable.h"
#include "Nodes/MeshInstance.h"
#include "Nodes/PointLight.h"
#include "Bindables/AllBindables.h"

class Mesh : public DrawableBase<Mesh>
{
public:
	Mesh(Graphics& gfx, std::vector<std::unique_ptr<Bindable>> bindPtrs)
	{
		if (!IsStaticInitialized())
		{
			AddStaticBindable(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		}

		for (auto& pb : bindPtrs)
		{
			if (auto pi = dynamic_cast<IndexBuffer*>(pb.get()))
			{
				AddIndexBuffer(std::unique_ptr<IndexBuffer>{ pi });
				pb.release();
			}
			else
			{
				AddBindable(std::move(pb));
			}
		}

		AddBindable(std::make_unique<TransformationConstantBuffer>(gfx, *this));
	}
	void SetLight(const PointLight& light)
	{
		pLight = &light;
	}
	void UnbindLight()
	{
		pLight = nullptr;
	}
	void Draw(Graphics& gfx) const override
	{
		if (pLight != nullptr)
		{
			pLight->Bind(gfx);
		}
		DrawableBase::Draw(gfx);
	}
private:
	const PointLight* pLight = nullptr;
};

std::shared_ptr<Mesh> ParseMesh(Graphics& gfx, const aiMesh& amesh, const aiMaterial* const* pMaterials);
std::unique_ptr<Node> ParseNode(const aiNode& anode, const std::vector<std::shared_ptr<Mesh>>& meshPtrs, aiMesh** const aiMeshes);

std::unique_ptr<Node> LoadModel(Graphics& gfx, const std::string& filename, const PointLight* pLight)
{
	Assimp::Importer imp;
	const aiScene* pModel = imp.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals);

	std::vector<std::shared_ptr<Mesh>> meshPtrs;
	meshPtrs.reserve(pModel->mNumMeshes);
	for (unsigned int i = 0; i < pModel->mNumMeshes; i++)
	{
		meshPtrs.push_back(ParseMesh(gfx, *pModel->mMeshes[i], pModel->mMaterials));
		if (pLight) meshPtrs[i]->SetLight(*pLight);
	}

	return ParseNode(*pModel->mRootNode, meshPtrs, pModel->mMeshes);
}

std::shared_ptr<Mesh> ParseMesh(Graphics& gfx, const aiMesh& amesh, const aiMaterial* const* pMaterials)
{
	using std::make_unique;
	using DynamicVertexBuf::VertexLayout;

	DynamicVertexBuf::VertexBuffer vbuf(
		std::move(
			VertexLayout{}
			.Append(VertexLayout::Position3D)
			.Append(VertexLayout::Normal)
			.Append(VertexLayout::Texture2D)
		)
	);
	
	std::vector<Index> indices;
	indices.reserve(amesh.mNumFaces * 3);
	for (unsigned int i = 0; i < amesh.mNumFaces; i++)
	{
		const auto& face = amesh.mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	for (unsigned int i = 0; i < amesh.mNumVertices; i++)
	{
		vbuf.EmplaceBack(
			*reinterpret_cast<float3*>(&amesh.mVertices[i]),
			*reinterpret_cast<float3*>(&amesh.mNormals[i]),
			*reinterpret_cast<float2*>(&amesh.mTextureCoords[0][i])
		);
	}

	std::vector<std::unique_ptr<Bindable>> bindablePtrs;

	if (amesh.mMaterialIndex >= 0)
	{
		using namespace std::string_literals;
		const aiMaterial& material = *pMaterials[amesh.mMaterialIndex];
		aiString texFileName;
		material.GetTexture(aiTextureType_DIFFUSE, 0, &texFileName);
		bindablePtrs.push_back(make_unique<Texture2D>(gfx, Surface("Models\\nano_textured\\"s + texFileName.C_Str())));
		bindablePtrs.push_back(make_unique<Sampler>(gfx));
	}

	bindablePtrs.push_back(std::make_unique<VertexBuffer>(gfx, vbuf));

	bindablePtrs.push_back(std::make_unique<IndexBuffer>(gfx, indices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"shaders-bin\\PhongVS.cso");
	auto pvsbc = pvs->GetBytecode();
	auto pvsbcs = pvs->GetBytecodeSize();
	bindablePtrs.push_back(std::move(pvs));

	bindablePtrs.push_back(std::make_unique<InputLayout>(gfx, vbuf.GetLayout().GetD3DLayout(), pvsbc, pvsbcs));

	bindablePtrs.push_back(std::make_unique<PixelShader>(gfx, L"shaders-bin\\PhongPS.cso"));

	struct PSMaterialConstant
	{
		float3 color = { 1.0f, 1.0f, 1.0f };
		float specularIntensity = 4.0f;
		float specularPower = 100;
		float3 padding;
	} pmc;
	bindablePtrs.push_back(std::make_unique<PixelConstantBuffer<PSMaterialConstant>>(gfx, pmc, 1u));

	return std::make_unique<Mesh>(gfx, std::move(bindablePtrs));
}

std::unique_ptr<Node> ParseNode(const aiNode& anode, const std::vector<std::shared_ptr<Mesh>>& meshPtrs, aiMesh** const aiMeshes)
{
	aiVector3D pos;
	aiVector3D rot;
	aiVector3D scaling;
	anode.mTransformation.Decompose(scaling, rot, pos);

	std::unique_ptr<Node> pNode;

	switch (anode.mNumMeshes)
	{
	case 0:
		pNode = std::make_unique<Node>(anode.mName.C_Str());
		break;
	case 1:
		pNode = std::make_unique<MeshInstance>(meshPtrs.at(anode.mMeshes[0]), anode.mName.C_Str());
		break;
	default:
		pNode = std::make_unique<Node>(anode.mName.C_Str());
		for (unsigned int i = 0; i < anode.mNumMeshes; i++)
		{
			auto& mesh = meshPtrs.at(anode.mMeshes[i]);
			pNode->AddChild(std::make_unique<MeshInstance>(mesh, aiMeshes[i]->mName.C_Str()));
		}
	}

	pNode->SetTransform(Transform(float3{ pos.x, pos.y, pos.z }, { rot.x, rot.y, rot.z }, { scaling.x, scaling.y, scaling.z }));

	for (unsigned int i = 0; i < anode.mNumChildren; i++)
	{
		pNode->AddChild(ParseNode(*anode.mChildren[i], meshPtrs, aiMeshes));
	}

	return pNode;
}
