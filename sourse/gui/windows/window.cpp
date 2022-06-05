#include "../../../headers/gui/windows/window.hpp"
#include "../../../headers/mics/exception.hpp"
#include "../../../headers/stdafx.h"
#include "../../../headers/mics/BitmapHelper.hpp"
#include <windowsx.h>
#include <gdiplus.h>
#include <sstream>
#include <pqxx/pqxx>
using namespace pqxx;
using namespace std;
Window::WindowClass Window::WindowClass::wndClass;
Window::WindowClass::WindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 6;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
#ifdef _DEBUG
	FILE* conout = stdout;
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen_s(&conout, "CONOUT$", "w", stdout);
#endif

}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

void Window::paint(HDC hdc)
{
	Graphics* gt = new Graphics(hdc);
	gt->SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);
	gt->SetCompositingMode(CompositingMode::CompositingModeSourceOver);
	gt->SetPixelOffsetMode(PixelOffsetMode::PixelOffsetModeHighQuality);
	gt->SetInterpolationMode(InterpolationMode::InterpolationModeHighQuality);
	gt->SetCompositingQuality(CompositingQuality::CompositingQualityHighQuality);
	/**********  Bitmaps  ************/
	gt->DrawCachedBitmap(bitmaps[eBitmaps::BitmapsList::bLogo].get(), 20, 0);
	/**********  Buttons  ************/
	buttons[eButtons::ButtonsList::uLoadData].get()->draw(gt);
	buttons[eButtons::ButtonsList::uGetData].get()->draw(gt);
	buttons[eButtons::ButtonsList::uInputData].get()->draw(gt);
	if (isDataOpen)
	{
		RectF origin(250.f, 50.f, 500.3f, 100.0f);
		Font myFont(L"Arial", 16);
		StringFormat sf(StringFormatFlagsNoClip);
		sf.SetLineAlignment(StringAlignment::StringAlignmentNear);
		SolidBrush white(Color(255, 100, 116, 123));
		SolidBrush blackBrush(Color(255, 255, 255, 255));
		buttons[eButtons::ButtonsList::uCloseData].get()->draw(gt);
		buttons[eButtons::ButtonsList::uNextData].get()->draw(gt);
		gt->FillRectangle(&white, 250.f, 50.f, 500.3f, 400.9f);
		wchar_t buff[100];
		for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
			swprintf(buff, 100, L"%d) »м€: %s Ч “лф.: %s", c[0].as<int>(), Helper::ConvertUtf8ToWide(c[1].as<string>()).c_str(), Helper::ConvertStringToWstring(c[2].as<string>()).c_str());
			gt->DrawString(
				buff,
				-1,
				&myFont,
				origin,
				&sf,
				&blackBrush);
			origin.Y += 30;
		}
	}
	/********** input ******************/
	if(isInputData)
		this->input.get()->Draw(gt);
	/********** InfoBox ******************/
	if (isInfoBox)
	{
		infoBox.get()->Draw(gt);
	}
	/**********  ProgressBar  ************/
	status.get()->drawBar(gt);
	status.get()->drawText(gt);
	delete gt;
}
void Window::DrawWarning(std::wstring text)
{
	DisableButton();
	infoBox.get()->SetText(text);
	isInfoBox = true;
	InvalidateRect(hWnd, 0, 1);
}
void Window::DisableWarning()
{
	EnableButton();
	infoBox.get()->SetText(L"");
	isInfoBox = false;
	InvalidateRect(hWnd, 0, 1);
}
const bool Window::isInput() const
{
	return isInputData;
}
void Window::DrawInput(std::wstring text)
{
	DisableButton();
	input.get()->SetText(text);
	isInputData = true;
	InvalidateRect(hWnd, 0, 1);
}
void Window::DisableInput()
{
	EnableButton();
	input.get()->SetText(L"");
	isInputData = false;
	InvalidateRect(hWnd, 0, 1);
}
void Window::LoadResources()
{
	Bitmap* bitmap = new Bitmap(L"..\\.\\.\\resoureses\\logo.png");
	/**********  Bitmaps  ************/
	bitmaps.push_back(BitmapHelper::createCachedBitmap(bitmap, GetDC(this->hWnd))); // logo = 0
	/**********  Buttons  ************/
	buttons.push_back(std::make_unique<Buttons>(L"Load Data\0", (Color(255, 62, 144, 232)),
		(Color(255, 255, 255)), (Color(255, 78, 60, 163)), RectF(40, 200, 180, 45))); // load data = 0
	buttons.push_back(std::make_unique<Buttons>(L"Get Data\0", (Color(255, 62, 144, 232)),
		(Color(255, 255, 255)), (Color(255, 78, 60, 163)), RectF(40, 250, 180, 45))); // get data info = 1
	buttons.push_back(std::make_unique<Buttons>(L"Input Data\0", (Color(255, 62, 144, 232)),
		(Color(255, 255, 255)), (Color(255, 78, 60, 163)), RectF(40, 300, 180, 45))); // input data info = 2
	buttons.push_back(std::make_unique<Buttons>(L"Close Data\0", (Color(255, 62, 144, 232)),
		(Color(255, 255, 255)), (Color(255, 78, 60, 163)), RectF(270, 470, 180, 45))); // close data info = 3
	buttons.push_back(std::make_unique<Buttons>(L"Next Data\0", (Color(255, 62, 144, 232)),
		(Color(255, 255, 255)), (Color(255, 78, 60, 163)), RectF(550, 470, 180, 45))); // next data info = 4
	/**********  ProgressBar  ************/
	status = make_unique<ProgressBar>(Rect(30, 550, 740, 30));
	/********** InfoBox *****************/
	infoBox = make_unique<InfoBox>();
	/********** input ******************/
	this->input = make_unique<class input>();
	this->input.get()->SetText(L"¬ведите им€");
	delete bitmap;
}
// Window Stuff
Window::Window(int width, int height, const char* name, bool isChaild)
	:
	width(width),
	height(height)
{
	// calculate window size based on desired client region size
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw CHWND_LAST_EXCEPT();
	}
	// create window & get hWnd
	if (isChaild)
	{
		hWnd = CreateWindow(
			WindowClass::GetName(), name,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_CHILD,
			CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr, WindowClass::GetInstance(), this
		);

	}
	else
	{
		hWnd = CreateWindow(
			WindowClass::GetName(), name,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			(GetSystemMetrics(SM_CXSCREEN) >> 1) - (width >> 1), (GetSystemMetrics(SM_CYSCREEN) >> 1) - (height >> 1), wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr, WindowClass::GetInstance(), this
		);
	}
	// check for error
	if (hWnd == nullptr)
	{
		throw CHWND_LAST_EXCEPT();
	}
	LoadResources();
	// show window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}
HWND& Window::GetHandle()
{
	return hWnd;
}
HRESULT Window::ConnectToServer(std::string host, std::string bd, std::string user, std::string pass, std::string port)
{
	if (s.get()->IsConnect())
		return (HRESULT)3;
	std::ostringstream oss;
	oss << "dbname = " << bd << " user = " << user << " password = " << pass << " \
		 hostaddr = " << host << " port = " << port ;
	s = make_unique< SQLQuery>();
	return s.get()->connect(oss.str());

}

const bool Window::CreateNewOrder(std::string name, std::string phone) const
{
	if (!s.get()->IsConnect())
		return false;
	std::ostringstream oss;
	oss << "set client_encoding='LATIN1';INSERT INTO foo(name,phone,status) VALUES ('" << name.c_str() << "','" << phone.c_str()
		<<"',false);set client_encoding='UTF8';";
	std::string codepage_str = oss.str();
	int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, codepage_str.c_str(),
		codepage_str.length(), nullptr, 0);
	std::wstring utf16_str(size, '\0');
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, codepage_str.c_str(),
		codepage_str.length(), &utf16_str[0], size);

	int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
		utf16_str.length(), nullptr, 0,
		nullptr, nullptr);
	std::string utf8_str(utf8_size, '\0');
	WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
		utf16_str.length(), &utf8_str[0], utf8_size,
		nullptr, nullptr);

	s.get()->queryInsert(utf8_str.c_str());
	return true;
}
void Window::GetInfoFromServer(std::string elemet, UINT16 MinCounts, UINT16 MaxCounts)
{
	if (!s.get()->IsConnect())
		return;
	std::ostringstream oss;
	oss << "SELECT * FROM " << elemet << " ORDER BY id OFFSET " << MinCounts << " ROWS \
		FETCH NEXT " << MaxCounts << " ROWS ONLY ";
	R = s.get()->query(oss.str());
	isDataOpen = true;
	InvalidateRect(hWnd, 0, true);

}
void Window::EnableButton(int id)
{
	if (id == -1)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			buttons.at(i).get()->EnableButton();
		}
	}
	else buttons.at(id).get()->EnableButton();
}

void Window::DisableButton(int id)
{
	if (id == -1)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			buttons[i].get()->DisableButton();
		}
	}
	else buttons.at(id).get()->DisableButton();
}
void Window::CloseData()
{
	isDataOpen = false;
}
Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::SetTitle(const std::string& title)
{
	if (SetWindowText(hWnd, title.c_str()) == 0)
	{
		throw CHWND_LAST_EXCEPT();
	}
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// forward message to window instance handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// retrieve ptr to window instance
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window instance handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	PAINTSTRUCT ps;
	RECT clientRect;
	HRGN bgRgn;
	HBRUSH hBrush;
	HDC hdc, mem_dc;
	HBITMAP mem_bitmap;
	switch (msg)
	{
		// we don't want the DefProc to handle this message because
		// we want our destructor to destroy the window, so return 0 instead of break
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		// clear keystate when window loses focus to prevent input getting "stuck"
	case WM_KILLFOCUS:
		kbd.ClearState();
		break;

		/*********** KEYBOARD MESSAGES ***********/
	case WM_KEYDOWN:
		// syskey commands need to be handled to track ALT key (VK_MENU) and F10
		
	case WM_SYSKEYDOWN:
		if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) // filter autorepeat
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;
		/*********** END KEYBOARD MESSAGES ***********/

		/************* MOUSE MESSAGES ****************/
	case WM_MOUSEMOVE:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		// in client region -> log move, and log enter + capture mouse (if not previously in window)
		if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
		{
			mouse.OnMouseMove(pt.x, pt.y);
			if (!mouse.IsInWindow())
			{
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		// not in client -> log move / maintain capture if button down
		else
		{
			if (wParam & (MK_LBUTTON | MK_RBUTTON))
			{
				mouse.OnMouseMove(pt.x, pt.y);
			}
			// button up -> release capture / log event for leaving
			else
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pt.x, pt.y);
		// release mouse if outside of window
		if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pt.x, pt.y);
		// release mouse if outside of window
		if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnWheelDelta(pt.x, pt.y, delta);
		break;
	}
	/************** END MOUSE MESSAGES **************/
	case WM_PAINT:
	{
		GetClientRect(hWnd, &clientRect);
		hdc = BeginPaint(hWnd, &ps);
		mem_dc = CreateCompatibleDC(hdc);
		mem_bitmap = CreateCompatibleBitmap(hdc, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		SelectObject(mem_dc, mem_bitmap);

		bgRgn = CreateRectRgnIndirect(&clientRect);
		hBrush = CreateSolidBrush(RGB(34, 44, 52));
		FillRgn(mem_dc, bgRgn, hBrush);
		paint(mem_dc);
		BitBlt(hdc, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, mem_dc, 0, 0, SRCCOPY);

		DeleteDC(mem_dc);
		DeleteObject(mem_bitmap);
		DeleteObject(bgRgn);
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_APP + 1:
		break;
	case WM_ERASEBKGND:
		return 1; // Suppress window erasing to reduce flickering
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
std::optional<int> Window::ProcessMessages()
{
	MSG msg;
	
	// while queue has messages, remove and dispatch them (but do not block on empty queue)
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		// check for quit because peekmessage does not signal this via return val
		if (msg.message == WM_QUIT)
		{
			// return optional wrapping int (arg to PostQuitMessage is in wparam) signals quit
			return (int)msg.wParam;
		}
		// TranslateMessage will post auxilliary WM_CHAR messages from key msgs
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// return empty optional when not quitting app
	return {};
}


// Window Exception Stuff
Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	:
	MyException(line, file),
	hr(hr)
{}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	// windows will allocate memory for err string and make our pointer point to it
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	// 0 string length returned indicates a failure
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	// copy error string from windows-allocated buffer to std::string
	std::string errorString = pMsgBuf;
	// free windows buffer
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}
