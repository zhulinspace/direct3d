#pragma once
#include"ChillWin.h"
#include <d3d11.h>
#include "chillException.h"
#include "DxgiInfoManager.h"
#include <vector>
#include <DirectXMath.h>
#include "ChillWRL.h"
#include<directX/Macros/GraphicsThrowMacros.h>

class Graphics
{
	friend class Bindable;
public:
	class Exception :public ChiliException
	{
		using ChiliException::ChiliException;
	};
	class HrException :public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {})noexcept;
		const char* what() const noexcept override;
		const char* GetType()const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo()const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException :public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
public:
	Graphics(HWND);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics()=default;
	void EndFrame();
	void DrawIndexed(UINT count) noexcept;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void ClearBuffer(float red, float green, float blue)noexcept
	{
		const float color[] = { red,green,blue,1.0f };
		pContext->ClearRenderTargetView(pTarget.Get(), color);
		pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);

	}
	void DrawTestTriangle(float angle,float x ,float y);
private:
	DirectX::XMMATRIX projection;
#ifdef DEBUG
	DxgiInfoManager infoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11Device>  pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap ;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>  pContext ;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  pTarget ;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>pDSV;
};

//hr need to be local 

//#define GFX_THROW_FAILED(hrcall) if(FAILED(hr=(hrcall))) throw Graphics::HrException(__LINE__,__FILE__,hr)
//#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException(__LINE__,__FILE__,hr)
//
//#define GFX_EXCEPT_NOINFO(hr) Graphics::HrException( __LINE__,__FILE__,(hr) )
//#define GFX_THROW_NOINFO(hrcall) if( FAILED( hr = (hrcall) ) ) throw Graphics::HrException( __LINE__,__FILE__,hr )
//
//#ifdef DEBUG
//#define GFX_EXCEPT(hr) Graphics::HrException( __LINE__,__FILE__,(hr),infoManager.GetMessages() )
//#define GFX_THROW_INFO(hrcall) infoManager.Set(); if( FAILED( hr = (hrcall) ) ) throw GFX_EXCEPT(hr)
//#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException( __LINE__,__FILE__,(hr),infoManager.GetMessages() )
//#define GFX_THROW_INFO_ONLY(call) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if(!v.empty()) {throw Graphics::InfoException( __LINE__,__FILE__,v);}}
//#else
//#define GFX_EXCEPT(hr) Graphics::HrException( __LINE__,__FILE__,(hr) )
//#define GFX_THROW_INFO(hrcall) GFX_THROW_NOINFO(hrcall)
//#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException( __LINE__,__FILE__,(hr) )
//#define GFX_THROW_INFO_ONLY(call) (call)
//#endif