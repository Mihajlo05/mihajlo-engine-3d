cbuffer TranfBuf
{
	matrix transformation;
};

struct VSOut
{
	float3 color : COLOR;
	float4 pos : SV_POSITION;
};

VSOut main( float3 pos : POSITION, float3 color : COLOR )
{
	VSOut vso;
	vso.color = color;

	float y = pos.y;

	vso.pos = mul(float4(pos.x, y, pos.z, 1.0f), transformation);
	return vso;
}