#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "../../../headers/mics/exception.hpp"
#include "../../../headers/mics/Mouse.hpp"
#include "../../../headers/mics/Keyboard.hpp"
#include <optional>
#include <memory>
#include "../../stdafx.h"
#include "../../mics/enumlist.h"
#include "../buttons.hpp"
#include <thread>
#include "../ProgressBar.hpp"
#include "../../../headers/mics/query.hpp"
#include "infoBox.hpp"
#include "input.hpp"
class Window
{
public:
	class Exception : public MyException
	{
	public:
		Exception( int line,const char* file,HRESULT hr ) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode( HRESULT hr ) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	// singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass( const WindowClass& ) = delete;
		WindowClass& operator=( const WindowClass& ) = delete;
		static constexpr const char* wndClassName = "GDI+ Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window( int width,int height,const char* name, bool isChaild = false);
	~Window();
	Window( const Window& ) = delete;
	Window& operator=( const Window& ) = delete;
	void SetTitle( const std::string& title );
	static std::optional<int> ProcessMessages();
	void CloseData();
private:
	static LRESULT CALLBACK HandleMsgSetup( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam ) noexcept;
	static LRESULT CALLBACK HandleMsgThunk( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam ) noexcept;
	LRESULT HandleMsg( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam ) noexcept;
	void paint(HDC);
	void LoadResources();
public:
	Keyboard kbd;
	Mouse mouse;
	std::unique_ptr<SQLQuery> s;
public:
	HWND& GetHandle();
	HRESULT ConnectToServer(std::string host, std::string bd, std::string user, std::string pass, std::string port);
	void GetInfoFromServer(std::string,  UINT16 MinCounts, UINT16 MaxCounts);
	const bool CreateNewOrder(std::string name, std::string phone) const;
	void DisableButton(int id = -1);
	void EnableButton(int id = -1);
	void DrawWarning(std::wstring);
	void DisableWarning();
	void DrawInput(std::wstring);
	void DisableInput();
	const bool isInput() const;
private:
	result R;
	HWND hWnd;
	int width;
	int height;
	bool isDataOpen = false;
	bool isInputData = false;
	bool isInfoBox = false;
public:
	std::vector<std::shared_ptr<CachedBitmap>> bitmaps;
	std::vector<std::unique_ptr<Buttons>> buttons;
	std::unique_ptr<InfoBox> infoBox;
	std::unique_ptr<input> input;

public:
	std::unique_ptr<ProgressBar> status;
};


// error exception helper macro
#define CHWND_EXCEPT( hr ) Window::Exception( __LINE__,__FILE__,hr )
#define CHWND_LAST_EXCEPT() Window::Exception( __LINE__,__FILE__,GetLastError() )
#endif // __WINDOW_H__