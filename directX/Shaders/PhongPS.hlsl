cbuffer LightCBuf
{
    float3 lightPos;
    float3 ambient ;
    float3 diffuseColor;
    float diffuseIntensity ;
    float attConst;
    float attLin;
    float attQuad;
};

cbuffer ObjectCBuf
{
    float3 materialColor;
    float specularIntensity;
    float specularPower;
};
// we just need two independent constant buffers so that means we need two slots

float4 main(float3 worldPos : Position, float3 n : Normal) : SV_Target
{
	// fragment to light vector data
    const float3 Light = lightPos - worldPos;
    const float distToLight = length(Light);
    const float3 LightDir = Light / distToLight;
	// diffuse attenuation
    const float att = 1.0f / (attConst + attLin * distToLight + attQuad * (distToLight * distToLight));
	// diffuse intensity
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(LightDir, n));
    
    const float3 W = n * dot(LightDir, n);
    const float3 r = W * 2.0f - LightDir;
    const float3 specular = (diffuseColor * diffuseIntensity) * specularIntensity * pow(max(0.0f, dot(normalize(r), normalize(worldPos))), specularPower);
	// final color
    return float4(saturate(diffuse + ambient+specular) * materialColor, 1.0f);
}