#include "Texture.h"
#include<directX/Surface.h>
#include"directX/Macros/GraphicsThrowMacros.h"

namespace wrl = Microsoft::WRL;

Texture::Texture(Graphics& gfx, const Surface& s)
{
	//import the inform manager
	INFOMAN(gfx);

	//create texture resource
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = s.GetWidth();
	textureDesc.Height = s.GetHeight();
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = s.GetBufferPtr();
	sd.SysMemPitch = s.GetWidth() * sizeof(Surface::Color);
	wrl::ComPtr<ID3D11Texture2D>pTexture;
	GFX_THROW_INFO(
		GetDevice(gfx)->CreateTexture2D(&textureDesc,&sd,&pTexture)
	);

	// create the resource view on the shader
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	GFX_THROW_INFO(
		GetDevice(gfx)->CreateShaderResourceView(
			pTexture.Get(),&srvDesc,&pTextureView
		)
	);

	

}

/*
specifies data for initializing a subresource
pSysMem: const void *
Pointer to the initialization data
SysMemPitch:
the distance (in bytes) from the begining of one line of a texture to the next line
it is  used only for 2D and 3d texture data as it is has no meaning for other resouces type
SysMemSlicePitch:
Specify the distance from the first pixel of one 2D slice of a 3D texture to the first pixel of the next 
2D slice in that texture in the SysMemSlicePitch member.
ID3D11Texture2D:
A 2D texture interface manages texel data, which is structured memory
*/

void Texture::Bind(Graphics& gfx) noexcept
{
	//we bind the view to the pipeline
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());
}
