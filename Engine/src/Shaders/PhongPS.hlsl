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

static const float3 materialColor = { 1.0f, 1.0f, 1.0f };
static const float specularIntensity = 1.2f;
static const float specularPower = 40.0f;

float4 main(float3 camPosition : POSITION, float3 normal : NORMAL) : SV_Target
{
    float3 vToL = lightPos - camPosition;
    float distToL = length(vToL);
    float3 dirToL = vToL / distToL;
    
    const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
    
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, normal));
    
    const float3 r = reflect(dirToL, normal);
    
    const float3 specular = att * (diffuseColor * diffuseIntensity) * specularIntensity *
    pow(max(0.0f, dot(normalize(r), normalize(camPosition))), specularPower);
	
    return float4(saturate((diffuse + ambient + specular) * materialColor), 1.0f);
}