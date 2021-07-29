#pragma once

#include "Nodes/Node.h"
#include "Bindables/PixelConstantBuffer.h"
#include "Nodes/MeshInstance.h"
#include "Drawables/Solid.h"
#include "Gui/imgui/imgui.h"

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
        auto psMesh = std::make_shared<Drawables::Solid>(gfx,
            IndexedTriangleList("Models\\sphere.obj"),
            data.diffuseColor);
        pMesh = psMesh.get();
        auto meshi = std::make_unique<MeshInstance>(std::move(psMesh), "Mesh");
        meshi->SetTransform(meshi->GetTransform().Scale(0.1f));
        AddChild(std::move(meshi));
    }
    void Bind(Graphics& gfx) const
    {
        CBufData cbufd;

        DXVec pos = DirectX::XMVector3Transform(GetTransform().pos, GetPrevTranfs());
        pos = DirectX::XMVector3Transform(pos, gfx.GetCamera().GetView());
        DirectX::XMStoreFloat3(&cbufd.camPos, pos);
        cbufd.other = data;

        pMesh->SetColor(data.diffuseColor);

        cbuf.Update(gfx, cbufd);
        cbuf.Bind(gfx);
    }
    virtual ~PointLight() = default;
protected:
    virtual void ShowOnInspector() override
    {
        ImGui::ColorPicker3("Ambijent", &data.ambient.x);
        ImGui::ColorPicker3("Boja", &data.diffuseColor.x);
        ImGui::SliderFloat("Intezitet", &data.diffuseIntensity, 0, 1);
        ImGui::InputFloat3("Atenuacija", &data.attConst);

        ImGui::NewLine();
        Node::ShowOnInspector();
    }
private:
    Drawables::Solid* pMesh = nullptr;
    Data data;
    PixelConstantBuffer<CBufData> cbuf;
};
