//struct  VSOut
//{
//	float3 color:Color;
//	float4 pos:SV_POSITION;
//	
//};
cbuffer CBuf
{
	 matrix transform;
	 // the shader expects the col major,it faster than the row major
};

float4 main(float3 pos : POSITION) :SV_Position
{
	/*VSOut vso;
	vso.pos =mul( float4(pos, 1.0f),transform);
	vso.color = color;
	return vso;*/
	return mul(float4(pos, 1.0f),transform);
}

