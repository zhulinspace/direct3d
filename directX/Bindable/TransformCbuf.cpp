#include "TransformCbuf.h"


TransformCbuf::TransformCbuf(Graphics& gfx, const Drawable& parent)
	:parent(parent)
{
	if (!pvcbuf)
	{
		pvcbuf = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(gfx);

	}
}

void TransformCbuf::Bind(Graphics& gfx) 
{
	pvcbuf->Update(
		gfx,
		DirectX::XMMatrixTranspose(
			parent.GetTransformXM() * gfx.GetProjection()
		)
	);
	pvcbuf->Bind(gfx);
}

//because it is staic variable we got to declare it down here like this
std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>>TransformCbuf::pvcbuf;