cbuffer LightCBuf
{
    float3 lightPos;
};

static const float3 materialColor = { 0.7f, 0.7f, 0.9f };
static const float3 ambient = { 0.15f, 0.15f, 0.15f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 1.0f;
static const float attConst = 1.0f;
static const float attLin = 0.045f;
static const float attQuad = 0.0075f;

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
	// final color
    return float4(saturate(diffuse + ambient), 1.0f);
}