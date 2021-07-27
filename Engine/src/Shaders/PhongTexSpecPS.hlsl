cbuffer CLightBuf
{
    float3 lightPos;
    float3 ambient;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

Texture2D tex : register(t0);
Texture2D specMap : register(t1);

SamplerState samp;

float4 main(float3 camPosition : POSITION, float3 normal : NORMAL, float2 texCoord : TEXCOORD) : SV_Target
{
    float3 vToL = lightPos - camPosition;
    float distToL = length(vToL);
    float3 dirToL = vToL / distToL;
    
    const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
    
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, normal));
    
    const float3 r = reflect(dirToL, normal);
    
    const float4 specSample = specMap.Sample(samp, texCoord);
    const float3 specularColorIntensity = specSample.rgb;
    const float specularPower = pow(2.0f, specSample.a * 13.0f);
    
    const float3 specular = att * specularColorIntensity *
    pow(max(0.0f, dot(normalize(r), normalize(camPosition))), specularPower);
	
    float3 texColor = (float3) tex.Sample(samp, texCoord);
    
    return float4(saturate((diffuse + ambient) * texColor + specular), 1.0f);
}