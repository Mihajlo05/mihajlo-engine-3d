Texture2D tex;

SamplerState sampState;

float4 main(float2 texPos : TEX_POSITION) : SV_TARGET
{
	return tex.Sample(sampState, texPos);
}