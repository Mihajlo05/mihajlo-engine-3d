#include "PointLight.h"

namespace dx = DirectX;

PointLight::PointLight(DirectX::XMVECTOR pos, Desc desc, Graphics& gfx)
	:
	ambient(desc.ambient),
	diffuseColor(desc.diffuseColor),
	diffuseIntensity(desc.diffuseIntensity),
	attConst(desc.attConst),
	attLin(desc.attLin),
	attQuad(desc.attQuad),
	model(gfx, diffuseColor),
	cbuf(gfx)
{ }

void PointLight::Bind(Graphics& gfx, DirectX::XMMATRIX view) const
{
	CBufData data;

	DirectX::XMVECTOR camPos = GetLocalTransform().Translate(GetGlobalTransform().pos).pos;
	camPos = DirectX::XMVector3Transform(camPos, view);

	dx::XMStoreFloat3( &data.pos, camPos);
	const float cf = 1.0f / 255.0f;
	data.ambient = { (float)ambient.GetR() * cf,
					(float)ambient.GetG() * cf,
					(float)ambient.GetB() * cf };
	data.diffuseColor = { (float)diffuseColor.GetR() * cf,
					(float)diffuseColor.GetG() * cf,
					(float)diffuseColor.GetB() * cf };
	data.diffuseIntensity = diffuseIntensity;
	data.attConst = attConst;
	data.attLin = attLin;
	data.attQuad = attQuad;

	cbuf.Update(gfx, data);
	cbuf.Bind(gfx);
}

void PointLight::Draw() const
{
	model.ResetTransformations();
	model.AddTransformation(GetTransfMatrix());
	model.Draw();
}
