#include "Drawable.h"
#include<directX/Macros/GraphicsThrowMacros.h>
#include<directX/Bindable/IndexBuffer.h>
#include<cassert>
#include<typeinfo>
void Drawable::Draw(Graphics& gfx) const noexcept
{
	for (auto& b : binds)
	{
		b->Bind(gfx);
	}// we bind all the instance binds

	//then we bind all the static binds
	for (auto& b : GetStaticBinds())
	{
		b->Bind(gfx);
	}

	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind) noexcept
{
	assert("*must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
	binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf) noexcept
{
	assert("attempt add index buffer second time" && pIndexBuffer == nullptr);
	pIndexBuffer = ibuf.get();
	binds.push_back(std::move(ibuf));
}



