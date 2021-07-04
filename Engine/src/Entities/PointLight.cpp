#include "PointLight.h"

PointLight::PointLight(Color c, Graphics& gfx)
	:
	color(c),
	model(gfx, c),
	cbuf(gfx)
{ }

void PointLight::Bind(Graphics& gfx, DirectX::XMMATRIX view) const
{
	CBufData data;

	DirectX::XMVECTOR camPos = GetLocalTransform().Translate(GetGlobalTransform().pos).pos;
	camPos = DirectX::XMVector3Transform(camPos, view);

	DirectX::XMStoreFloat3( &data.pos, camPos);
	cbuf.Update(gfx, data);
	cbuf.Bind(gfx);
}

void PointLight::Draw() const
{
	model.ResetTransformations();
	model.AddTransformation(GetTransfMatrix());
	model.Draw();
}
