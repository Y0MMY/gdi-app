#include "App.hpp"
#include <sstream>
#include <iomanip>
#include "headers/GDI/GDIPlusManager.hpp"
#include <thread>

GDIPlusManager gdipm;
static UINT16 counts;
App::App()
	:
	wnd(800, 600, "The Donkey Fart Box :)")

{}

int App::Go()
{

	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;

		}
		DoFrame();
	}
}

void App::DoFrame()
{
	while (const unsigned char e = wnd.kbd.ReadChar())
	{
		wnd.input.get()->update((UINT)e, wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
	}
	while (const auto e = wnd.mouse.Read())
	{
		switch (e->GetType())
		{
			case Mouse::Event::Type::Move:
			{
				std::ostringstream oss; 
				oss << "Mouse moved to: (" << e->GetPosX() << "," << e->GetPosY() << ")\n";
				wnd.SetTitle(oss.str());
				wnd.buttons[eButtons::ButtonsList::uLoadData].get()->mouseMoved(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.buttons[eButtons::ButtonsList::uGetData].get()->mouseMoved(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.buttons[eButtons::ButtonsList::uInputData].get()->mouseMoved(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.buttons[eButtons::ButtonsList::uCloseData].get()->mouseMoved(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.buttons[eButtons::ButtonsList::uNextData].get()->mouseMoved(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.infoBox.get()->closeInfo.get()->mouseMoved(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.input.get()->closeInfo.get()->mouseMoved(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				break;
			}
			case Mouse::Event::Type::LPress:
			{
				wnd.buttons[eButtons::ButtonsList::uLoadData].get()->mouseReleased(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.buttons[eButtons::ButtonsList::uGetData].get()->mouseReleased(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.buttons[eButtons::ButtonsList::uInputData].get()->mouseReleased(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.buttons[eButtons::ButtonsList::uCloseData].get()->mouseReleased(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.buttons[eButtons::ButtonsList::uNextData].get()->mouseReleased(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.infoBox.get()->closeInfo.get()->mouseReleased(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.input.get()->closeInfo.get()->mouseReleased(wnd.GetHandle(), e->GetPosX(), e->GetPosY());
				wnd.input.get()->ClickInput(wnd.GetHandle(),wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
				if (wnd.infoBox.get()->closeInfo.get()->isClicked())
				{
					wnd.DisableWarning();
					return;
				}
				if (wnd.buttons[eButtons::ButtonsList::uLoadData].get()->isClicked())
				{
					if (wnd.s.get()->IsConnect()) 
					{
						wnd.DrawWarning(L"Вы уже подключились к базе данных!");
						return;
					}
					wnd.status.get()->ActionDraw();
					wnd.status.get()->SetString(L"Trying to connect to server...  0%");
					wnd.status.get()->invalidateProgressBar(wnd.GetHandle());
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					th = std::make_unique<std::thread>([&]() {
						std::this_thread::sleep_for(std::chrono::milliseconds(1200));
						wnd.status.get()->SetString(L"Setting up the environment...  80%");
						wnd.status.get()->invalidateProgressBar(wnd.GetHandle());
						wnd.status.get()->setValue(80);
						std::this_thread::sleep_for(std::chrono::milliseconds(800));
						if (wnd.ConnectToServer("127.0.0.1", "testcpp", "postgres", "123123", "5432") == (HRESULT)S_OK)
						{
							wnd.status.get()->SetString(L"All is done!  100%");
							wnd.status.get()->invalidateProgressBar(wnd.GetHandle());
							wnd.status.get()->setValue(100);
						}
						else
						{
							wnd.status.get()->SetString(L"Something gone wrong... Error to connect to database");
							wnd.status.get()->invalidateProgressBar(wnd.GetHandle());
							wnd.status.get()->setValue(100);
						}
						std::this_thread::sleep_for(std::chrono::milliseconds(400));
						wnd.status.get()->ActionDraw();
						wnd.status.get()->invalidateProgressBar(wnd.GetHandle());

					});
					if (th.get()->joinable()) th.get()->detach();
				}
				if (wnd.buttons[eButtons::ButtonsList::uGetData].get()->isClicked())
				{
					if (!wnd.s.get()->IsConnect()) 
					{
						wnd.DrawWarning(L"Для начала необходимо подключиться к базе данных!\n\nНажмите на кнопку \"Load Data\"");
						return;
					}
					counts = 10;
					wnd.status.get()->ActionDraw();
					wnd.status.get()->setValue(0);
					wnd.status.get()->SetString(L"Getting info...  0%");
					wnd.status.get()->invalidateProgressBar(wnd.GetHandle());
					th = std::make_unique<std::thread>([&](){
						std::this_thread::sleep_for(std::chrono::milliseconds(400));
						wnd.GetInfoFromServer("foo", 0, counts);
						wnd.status.get()->SetString(L"All is done!  100%");
						wnd.status.get()->invalidateProgressBar(wnd.GetHandle());
						wnd.status.get()->setValue(100);
						std::this_thread::sleep_for(std::chrono::milliseconds(400));
						wnd.status.get()->ActionDraw();
						wnd.status.get()->invalidateProgressBar(wnd.GetHandle());
					});
					if (th.get()->joinable()) th.get()->detach();
				}
				if (wnd.buttons[eButtons::ButtonsList::uCloseData].get()->isClicked())
				{
					wnd.CloseData();
					InvalidateRect(wnd.GetHandle(), 0, true);
				}
				if (wnd.buttons[eButtons::ButtonsList::uNextData].get()->isClicked())
				{
					counts += 10;
					wnd.GetInfoFromServer("foo", counts - 10, counts);
				}
				break;
			}
		}
	}

}