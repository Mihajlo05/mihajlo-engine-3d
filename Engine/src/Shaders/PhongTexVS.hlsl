cbuffer TransformationCBuf
{
    matrix modelView;
    matrix modelViewProj;
};

struct VSOut
{
    float3 camPos : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : POSITION, float3 normal : NORMAL, float2 texCoord : TEXCOORD)
{
    VSOut vso;
    vso.camPos = (float3) mul(float4(pos, 1.0f), modelView);
    vso.normal = mul(normal, (float3x3) modelView);
    vso.texCoord = texCoord;
    vso.pos = mul(float4(pos, 1.0f), modelViewProj);
    return vso;
}
