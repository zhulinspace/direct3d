#include "VertexShader.h"
#include<directX/Macros/GraphicsThrowMacros.h>
#include<directX/Bindable/BindableCodex.h>
#include<directX/ChillUtil.h>
VertexShader::VertexShader(Graphics& gfx, const std::string& path)
	:
	path(path)
{
	INFOMAN(gfx);

	GFX_THROW_INFO(D3DReadFileToBlob(ToWide("Shaders/" + path).c_str(), &pBytecodeBlob));
	//GFX_THROW_INFO(D3DReadFileToBlob(L"Shaders/ColorIndexVS.cso", &pBytecodeBlob));

	
	GFX_THROW_INFO(GetDevice(gfx)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&pVertexShader
	));
}

void VertexShader::Bind(Graphics& gfx) 
{
	INFOMAN_NOHR(gfx);
	GFX_THROW_INFO_ONLY(GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u));
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}
std::shared_ptr<VertexShader> VertexShader::Resolve(Graphics& gfx, const std::string& path)
{
	return Codex::Resolve<VertexShader>(gfx, path);
}
std::string VertexShader::GenerateUID(const std::string& path)
{
	using namespace std::string_literals;
	return typeid(VertexShader).name() + "#"s + path;
}
std::string VertexShader::GetUID() const noexcept
{
	return GenerateUID(path);
}