cbuffer CBuf
{
	float4 colors[6];
};

float4 main(uint id : SV_PrimitiveID) : SV_TARGET
{
	return colors[id / 2];
}