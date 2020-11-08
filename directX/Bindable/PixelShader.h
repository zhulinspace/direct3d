#pragma once
#include<directX/Bindable/Bindable.h>
#include<memory>
#include<d3dcompiler.h>
class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& gfx, const std::string& path);
	void Bind(Graphics& gfx) override;
	static std::shared_ptr<PixelShader> Resolve(Graphics& gfx, const std::string& path);
	static std::string GenerateUID(const std::string& path);
	std::string GetUID() const noexcept ;
protected:
	std::string path;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};