#pragma once

#include "Nodes/Node.h"
#include "Bindables/PixelConstantBuffer.h"
#include "Nodes/Meshes/Mesh.h"
#include "Drawables/SolidDrawable.h"

class PointLight : public Node
{
public:
    struct Data
    {
        alignas(16) float3 ambient;
        alignas(16) float3 diffuseColor;
        float  diffuseIntensity;
        float  attConst;
        float  attLin;
        float  attQuad;
    };
public:
    struct CBufData
    {
        alignas(16) float3 camPos;
        Data other;
    };
public:
    PointLight(Graphics& gfx, Data data, const std::string& name)
        :
        Node(name),
        data(data),
        cbuf(gfx)
    {
        auto psMesh = std::make_shared<SolidDrawable>(gfx,
            IndexedTriangleList("src\\Models\\sphere.obj"),
            data.diffuseColor);
        pMesh = psMesh.get();
        auto meshi = std::make_unique<MeshInstance>(std::move(psMesh), "Mesh");
        meshi->SetTransform(meshi->GetTransform().Scale(0.1f));
        AddChild(std::move(meshi));
    }
    void Bind(Graphics& gfx) const
    {
        CBufData cbufd;

        DXVec pos = GetTransform().pos;
        pos = DirectX::XMVector3Transform(pos, gfx.GetCamera());
        DirectX::XMStoreFloat3(&cbufd.camPos, pos);
        cbufd.other = data;

        pMesh->SetColor(data.diffuseColor);

        cbuf.Update(gfx, cbufd);
        cbuf.Bind(gfx);
    }
private:
    SolidDrawable* pMesh = nullptr;
    Data data;
    PixelConstantBuffer<CBufData> cbuf;
};
