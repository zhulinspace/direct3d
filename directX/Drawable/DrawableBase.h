#pragma once
#include<directX/Drawable/Drawable.h>
#include<directX/Bindable/IndexBuffer.h>

template<class T>
class DrawableBase :public Drawable
{
protected:
	bool IsStaticInitialized()const noexcept
	{
		return !staticBinds.empty();
	}

	static void AddStaticBind(std::unique_ptr<Bindable>bind)noexcept
	{
		assert("*must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
		staticBinds.push_back(std::move(bind));
	}

	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer>ibuf)noexcept
	{
		assert(pIndexBuffer == nullptr);
		pIndexBuffer = ibuf.get();
		staticBinds.push_back(std::move(ibuf));
	}

	void SetIndexFromStatic()noexcept
	{
		assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
		for (const auto& b : staticBinds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
			{//利用dynamic_cast检查b是不是indexbuffer类型，是则返回指针
				pIndexBuffer = p;
				return;
			}
		}
		assert("Failed to find index buffer in static binds" && pIndexBuffer != nullptr);
	}
private:
	const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds()const noexcept
	{
		return staticBinds;

	}
private:
	static std::vector<std::unique_ptr<Bindable>>staticBinds;
};
//here we are assuming that there is going to be at least one static bindable 

template<class T>
std::vector<std::unique_ptr<Bindable>>DrawableBase<T>::staticBinds;