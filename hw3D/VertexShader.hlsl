cbuffer CBuf
{
	matrix transformation;
};

struct VSOut
{
	float3 color : COLOR;
	float phase : PHASE;
	float4 pos : SV_POSITION;
};

VSOut main(float3 pos : POSITION, float3 color : COLOR, float phase : PHASE)
{
	VSOut vso;
	vso.color = color;
	vso.phase = phase;
	vso.pos = mul(float4(pos, 1.0f), transformation);
	return vso;
}