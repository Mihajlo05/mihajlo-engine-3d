cbuffer CLightBuf : register(b0)
{
    float3 lightPos;
    float3 ambient;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

cbuffer CMaterialBuf : register(b1)
{
    float specularIntensity;
    float specularPower;
};

Texture2D tex;
SamplerState samp;

float4 main(float3 camPosition : POSITION, float3 normal : NORMAL, float2 texCoord : TEXCOORD) : SV_Target
{
    float3 vToL = lightPos - camPosition;
    float distToL = length(vToL);
    float3 dirToL = vToL / distToL;
    
    const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
    
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, normal));
    
    const float3 r = reflect(dirToL, normal);
    
    const float3 specular = att * (diffuseColor * diffuseIntensity) * specularIntensity *
    pow(max(0.0f, dot(normalize(r), normalize(camPosition))), specularPower);
	
    float3 texColor = (float3) tex.Sample(samp, texCoord);
    
    return float4(saturate((diffuse + ambient) * texColor + specular), 1.0f);
}