cbuffer CBuf
{
    float3 lightPos;
    float3 ambient;
    float3 diffuseColor;
    float  diffuseIntensity;
    float  attConst;
    float  attLin;
    float  attQuad;
};

static const float3 materialColor = { 0.7f, 0.7f, 0.7f };

float4 main(float3 camPostion : POSITION, float3 normal : NORMAL) : SV_Target
{
    float3 vToL = lightPos - camPostion;
    float distToL = length(vToL);
    float3 dirToL = vToL / distToL;
    
    const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
    
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, normal));
    
    return float4(saturate(diffuse + ambient) * materialColor, 1.0f);
}