#pragma once
#include<directX/Bindable/ConstantBuffers.h>
#include<directX/Drawable/Drawable.h>
#include<DirectXMath.h>

class TransformCbuf :public Bindable
{
public:
	TransformCbuf(Graphics& gfx, const Drawable& parent,UINT slot=0u);
	void Bind(Graphics& gfx) override;
private:

	struct Transforms
	{
		DirectX::XMMATRIX modelViewProj;
		DirectX::XMMATRIX model;
	};

	
	static std::unique_ptr < VertexConstantBuffer<Transforms>>pvcbuf;
	//use static veretxconstbuffer to increase effenicy
	const Drawable& parent;

	
};