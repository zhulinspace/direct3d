#include "Box.h"
#include<directX/Bindable/VertexBuffer.h>
#include<directX/Bindable/IndexBuffer.h>
#include<directX/Bindable/ConstantBuffers.h>
#include<directX/Bindable/VertexShader.h>
#include<directX/Bindable/PixelShader.h>
#include<directX/Bindable/InputLayout.h>
#include<directX/Bindable/Topology.h>
#include<directX/Bindable/TransformCbuf.h>

Box::Box(Graphics& gfx, std::mt19937& rng, 
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist, 
	std::uniform_real_distribution<float>& odist, 
	std::uniform_real_distribution<float>& rdist)
	:
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
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			struct
			{
				float x;
				float y;
				float z;
			}pos;

		};

		const std::vector<Vertex>vertices =
		{
			{-1.0f,-1.0f,-1.0f},
			{1.0f,-1.0f,-1.0f },
			{-1.0f,1.0f,-1.0f},
			{1.0f,1.0f,-1.0f },
			{-1.0f,-1.0f,1.0f },
			{1.0f,-1.0f,1.0f },
			{-1.0f,1.0f,1.0f },
			{1.0f,1.0f,1.0f  },
		};
		const std::vector<unsigned short> indices =
		{
			0,2,1,2,3,1,
			1,3,5,3,7,5,
			2,6,3,3,6,7,
			4,5,7,4,7,6,
			0,4,2,2,4,6,
			0,1,4,1,5,4

		};
		//°ó¶¨vertex buffer
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

		//°ó¶¨indexbuffer
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		//bind vertexshader
		auto pvs = std::make_unique<VertexShader>(gfx, "VertexSahder.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		//bind pixel shader
		AddStaticBind(std::make_unique<PixelShader>(gfx, "PixelShader.cso"));

		struct ConstBuffer2
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			}face_colors[6];
		};

		const ConstBuffer2 cb2 =
		{
			{
				{1.0f,0.0f,1.0f},
				{1.0f,0.0f,0.0f},
				{0.0f,1.0f,0.0f},
				{0.0f,0.0f,1.0f},
				{1.0f,1.0f,0.0f},
				{0.0f,1.0f,1.0f},
			}
		};
		//bind pixel constant buffer
		AddStaticBind(std::make_unique<PixelConstantBuffer<ConstBuffer2>>(gfx, cb2));
		const std::vector<D3D11_INPUT_ELEMENT_DESC>ied =
		{
			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},

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


}

void Box::Update(float dt) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += yaw * dt;
	theta += theta * dt;
	phi += phi * dt;
	chi += chi * dt;
}

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll)*
		DirectX::XMMatrixTranslation(r,0.0f,0.0f)*
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi)*
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}
