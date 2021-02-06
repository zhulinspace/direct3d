#include "Box.h"
#include<directX/Bindable/VertexBuffer.h>
#include<directX/Bindable/IndexBuffer.h>
#include<directX/Bindable/ConstantBuffers.h>
#include<directX/Bindable/VertexShader.h>
#include<directX/Bindable/PixelShader.h>
#include<directX/Bindable/InputLayout.h>
#include<directX/Bindable/Topology.h>
#include<directX/Bindable/TransformCbuf.h>
#include<directX/Drawable/Geometric primitives/Cube.h>
#include<directX/Drawable/Geometric primitives/Sphere.h>

Box::Box(Graphics& gfx, std::mt19937& rng, 
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist, 
	std::uniform_real_distribution<float>& odist, 
	std::uniform_real_distribution<float>& rdist,
	std::uniform_real_distribution<float>& bdist,
	DirectX::XMFLOAT3 material)
	:
	// uniform_real_distribution生成指定范围的随机实数
	r(rdist(rng)),
	droll(ddist(rng)),
	dpitch(ddist(rng)),
	dyaw(ddist(rng)),
	dphi(odist(rng)),
	dtheta(odist(rng)),
	dchi(odist(rng)),
	chi(adist(rng)),
	theta(adist(rng)),
	phi(adist(rng))
{
	namespace dx = DirectX;
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			dx::XMFLOAT3 n;
		};

		auto model = Cube::MakeIndependent<Vertex>();
		model.SetNormalsIndependentFlat();
		//model.Transform(dx::XMMatrixScaling(1.0f, 1.0f, 1.2f));

		//绑定vertex buffer
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

		//绑定indexbuffer
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		//bind vertexshader
		auto pvs = std::make_unique<VertexShader>(gfx, "PhongVS.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		//bind pixel shader
		AddStaticBind(std::make_unique<PixelShader>(gfx, "PhongPS.cso"));

		
		const std::vector<D3D11_INPUT_ELEMENT_DESC>ied =
		{
			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },

		};

		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));
		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		
	}
	else
	{
		SetIndexFromStatic();
	}
	
	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
	//every box has its own individual transform so we do not bind static

	struct PSMaterialConstant
	{
		alignas(16) dx::XMFLOAT3 color;
		float specularIntensity = 0.6f;
		float specularPower = 30.0f;
		float padding[2];
	} colorConst;
	colorConst.color = material;
	AddBind(std::make_unique<PixelConstantBuffer<PSMaterialConstant>>(gfx, colorConst, 1u));


	// model deformation transform (per instance, not stored as bind)
	dx::XMStoreFloat3x3(
		&mt,
		dx::XMMatrixScaling(1.0f, 1.0f, bdist(rng))
	);

}

void Box::Update(float dt) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMLoadFloat3x3(&mt) *
		dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		dx::XMMatrixTranslation(r, 0.0f, 0.0f) *
		dx::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}
