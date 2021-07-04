cbuffer CBuf
{
    float3 lightPos;
};

static const float3 materialColor = { 0.7f, 0.7f, 0.9f };
static const float3 ambient = { 0.05f, 0.05f, 0.05f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 1.0f;
static const float attConst = 0.2f;
static const float attLin = 0.045f;
static const float attQuad = 0.0075f;

float4 main(float3 camPostion : POSITION, float3 normal : NORMAL) : SV_Target
{
    float3 vToL = lightPos - camPostion;
    float distToL = length(vToL);
    float3 dirToL = vToL / distToL;
    
    const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
    
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, normal));
    
    return float4(saturate(diffuse + ambient) * materialColor, 1.0f);
}