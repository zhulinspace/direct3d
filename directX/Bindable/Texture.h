#pragma once
#include "Bindable.h"

class Texture :public Bindable
{
public:
	Texture(Graphics& gfx, const class Surface& s);
	void Bind(Graphics& gfx) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>pTextureView;
	

	/*
	A shader-resource-view interface specifies the subresources a shader can access during rendering. Examples of shader
	resources include a constant buffer, a texture buffer, and a texture.
	*/

};