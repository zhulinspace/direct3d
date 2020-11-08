#pragma once
#include<directX/Bindable/ConstantBuffers.h>
#include<directX/Drawable/Drawable.h>
#include<DirectXMath.h>

class TransformCbuf :public Bindable
{
public:
	TransformCbuf(Graphics& gfx, const Drawable& parent);
	void Bind(Graphics& gfx) override;
private:
	//VertexConstantBuffer<DirectX::XMMATRIX>vcbuf;
	static std::unique_ptr < VertexConstantBuffer<DirectX::XMMATRIX>>pvcbuf;
	//use static veretxconstbuffer to increase effenicy
	const Drawable& parent;
};