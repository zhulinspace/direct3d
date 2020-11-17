#include "TransformCbuf.h"


TransformCbuf::TransformCbuf(Graphics& gfx, const Drawable& parent)
	:parent(parent)
{
	if (!pvcbuf)
	{
		pvcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx);

	}
}

void TransformCbuf::Bind(Graphics& gfx) 
{
	const auto model = parent.GetTransformXM();
	const Transforms tf =
	{
		DirectX::XMMatrixTranspose(model),
		DirectX::XMMatrixTranspose(
			model * gfx.GetCamera()*gfx.GetProjection()
		)
	};
	pvcbuf->Update(gfx,tf);
	pvcbuf->Bind(gfx);
}

//because it is staic variable we got to declare it down here like this
std::unique_ptr<VertexConstantBuffer<TransformCbuf::Transforms>>TransformCbuf::pvcbuf;