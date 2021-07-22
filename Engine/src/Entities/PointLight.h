#pragma once

#include "Entity.h"
#include "Drawables/SolidDrawable.h"
#include "Bindables/PixelConstantBuffer.h"
#include "imgui/imgui.h"

class PointLight : public Entity
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
private:
    struct CBufData
    {
        alignas(16) float3 camPos;
        Data other;
    };
public:
    PointLight(Graphics& gfx, Data data, const std::string& name)
        :
        Entity(name),
        model(gfx, IndexedTriangleList("src\\ModelFiles\\sphere.obj"),
            { data.diffuseColor.x * data.diffuseIntensity,
              data.diffuseColor.y * data.diffuseIntensity,
              data.diffuseColor.z * data.diffuseIntensity }),
        data(data),
        cbuf(gfx)
    {
        SetTransform(GetTransform().Scale(0.1f));
    }
    void Bind(Graphics& gfx) const
    {
        CBufData cbufd;

        DXVec pos = GetTransform().pos;
        pos = DirectX::XMVector3Transform(pos, gfx.GetCamera());
        DirectX::XMStoreFloat3(&cbufd.camPos, pos);
        cbufd.other = data;

        cbuf.Update(gfx, cbufd);
        cbuf.Bind(gfx);
    }
    void Draw(Graphics& gfx) override
    {
        model.SetTransformation(GetTransform().GetMatrix());
        model.Draw(gfx);
    }
    void SpawnControllWindow() override
    {
        Entity::SpawnControllWindow();

        if (ImGui::Begin(GetName().c_str()))
        {
            ImGui::ColorPicker3("Ambijent", &data.ambient.x);
            ImGui::ColorPicker3("Boja", &data.diffuseColor.x);
            model.SetColor(data.diffuseColor);
            ImGui::SliderFloat("Intezitet difuzije", &data.diffuseIntensity, 0.0f, 1.0f);
            ImGui::InputFloat3("Atenuacija", &data.attConst);
        }
        ImGui::End();
    }
private:
    SolidDrawable model;
    Data data;
    PixelConstantBuffer<CBufData> cbuf;
};