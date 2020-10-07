#pragma once
//just remember include chiliwin first
#include "ChillWin.h"
#include "chillException.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Graphic.h"
#include<optional>
#include <memory>

// the window class should 封装窗口的创建 ，销毁，以及对消息的处理
class Window
{
public:
	// in window class so it's gonna be a window exception inherits from chillexception
	class Exception : public ChiliException
	{
		using ChiliException::ChiliException;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
	};
	
private:
	// we only need one window class we're going to make this a singleton
	class WindowClass
	{
		public:
			static const char* GetName() noexcept;
			static HINSTANCE GetInstance()noexcept;
		private:
			WindowClass()noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const char* wndClassName = "Chili Direct3D Engine Window";
			static WindowClass wndClass;
			HINSTANCE hInst;
	};

public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string title);
	static std::optional<int>ProcessMessages();
	Graphics& Gfx();

private:
	//Windows callback label can't be used in  member function 
	//becase member functio takes a hidden parameter that 
	//is the pointer to the instance on which the member function is being called
	// windows api does't know c++，also dose't know member function
	// static function is almostly free function
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	// handle window messages
public:
	Keyboard kbd;
	Mouse mouse;
	
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};

#define CHWND_EXCEPT( hr ) Window::HrException( __LINE__,__FILE__,(hr) )
#define CHWND_LAST_EXCEPT() Window::HrException( __LINE__,__FILE__,GetLastError() )
#define CHWND_NOGFX_EXCEPT() Window::NoGfxException( __LINE__,__FILE__ )