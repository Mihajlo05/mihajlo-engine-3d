#pragma once

#include "Entity.h"
#include "Drawables/SolidDrawable.h"
#include "Bindables/PixelConstantBuffer.h"

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
    PointLight(Graphics& gfx, Data data)
        :
        model(gfx, IndexedTriangleList("src\\ModelFiles\\sphere.obj")),
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
private:
    SolidDrawable model;
    Data data;
    PixelConstantBuffer<CBufData> cbuf;
};