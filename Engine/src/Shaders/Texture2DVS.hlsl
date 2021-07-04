cbuffer TransfCBuf
{
	matrix transformation;
};

struct VSOut
{
	float2 texPos : TEX_POSITION;
	float4 pos : SV_POSITION;
};

VSOut main(float3 pos : POSITION, float2 texPos : TEX_POSITION)
{
	VSOut vso;
	vso.texPos = texPos;
	vso.pos = mul(float4(pos, 1.0f), transformation);
	return vso;
}