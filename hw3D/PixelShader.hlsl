
cbuffer CBuf
{
	float time, t1, t2, t3;
};

float4 main(float3 color : COLOR, float phase : PHASE) : SV_TARGET
{
	return pow(sin(2 * 3.14f * 0.5f * time + phase), 2.0f) * float4(color, 1.0f);
}