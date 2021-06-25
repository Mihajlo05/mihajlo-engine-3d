#include "Box.h"

PixelConstantBuffer<PBuf>* Box::pcb;

Box::Box(Graphics& gfx)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			struct { float x, y, z; } pos;
			struct { float r, g, b; } color;
			float phase;
		};

		const float pif = 3.14f / 4.0f;

		std::vector<Vertex> vertices =
		{
			{ -1.0f,-1.0f,-1.0f, 1.0f, 1.0f, 1.0f, pif },
			{ 1.0f,-1.0f,-1.0f, 1.0f, 1.0f, 0.0f, 2 * pif },
			{ -1.0f,1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 3 * pif },
			{ 1.0f,1.0f,-1.0f, 0.0f, 1.0f, 1.0f, 4 * pif},
			{ -1.0f,-1.0f,1.0f, 1.0f, 0.0f, 0.0f, 5 * pif},
			{ 1.0f,-1.0f,1.0f, 0.0f, 1.0f, 0.0f, 6 * pif },
			{ -1.0f,1.0f,1.0f, 0.0f, 0.0f, 0.0f, 7 * pif },
			{ 1.0f,1.0f,1.0f, 0.0f, 0.0f, 0.0f, 8 * pif}
		};

		std::vector<unsigned short> indices = {
				0,2,1, 2,3,1,
				1,3,5, 3,7,5,
				2,6,3, 3,6,7,
				4,5,7, 4,7,6,
				0,4,2, 2,4,6,
				0,1,4, 1,5,4
		};

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		AddStaticBindable(std::make_unique<VertexBuffer>(gfx, vertices));

		AddStaticBindable(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		VertexShader& vs = *pvs;
		AddStaticBindable(std::move(pvs));

		std::vector<D3D11_INPUT_ELEMENT_DESC> iedsc;
		iedsc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		iedsc.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0 });
		iedsc.push_back({ "PHASE", 0, DXGI_FORMAT_R32_FLOAT, 0, 6 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0 });

		AddStaticBindable(std::make_unique<InputLayout>(gfx, iedsc, vs.GetBytecode(), vs.GetBytecodeSize()));

		AddStaticBindable(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		PBuf pb = { time, 0.0f, 0.0f, 0.0f };
		auto upcb = std::make_unique<PixelConstantBuffer<PBuf>>(gfx, pb);
		pcb = upcb.get();
		AddStaticBindable(std::move(upcb));
	}
	else
	{
		AddIndexBufferFromStatic();
	}

	std::random_device rd;
	std::mt19937 rng(rd());

	std::uniform_real_distribution<float> dist(0.0f, 6.28f / 10.0f);

	dpitch = dist(rng);
	dyaw = dist(rng);
	droll = dist(rng);

	AddBindable(std::make_unique<TransformationConstantBuffer>(gfx, *this));
}

void Box::Update(float dt, Graphics& gfx)
{
	time += dt;

	pitch += dpitch * dt;
	yaw += dyaw * dt;
	roll += droll * dt;

	PBuf pb = { time, 0.0f, 0.0f, 0.0f };
	pcb->Update(gfx, pb);
}

DirectX::XMMATRIX Box::GetTransformation() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(10.0f, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 15.0f);
}
