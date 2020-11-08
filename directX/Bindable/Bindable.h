#pragma once
#include<directX/Graphic.h>

class Bindable
{
public:
	virtual void Bind(Graphics& gfx) = 0;
	virtual ~Bindable() = default;
	virtual std::string GetUID() const noexcept
	{
		assert(false);
		return "";
	}
protected:
	static ID3D11DeviceContext* GetContext(Graphics& gfx)noexcept
	{
		return *gfx.pContext.GetAddressOf();
	}
	static ID3D11Device* GetDevice(Graphics& gfx)noexcept
	{
		return *gfx.pDevice.GetAddressOf();
	}
	static DxgiInfoManager& GetInfoManager(Graphics& gfx)noexcept
	{
		return gfx.infoManager;
	}
};