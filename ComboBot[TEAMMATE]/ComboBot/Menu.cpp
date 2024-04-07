#include "pch.h"
#include <boost/asio.hpp>



void Menu::HandleMsgs()
{
	while (GetMessage(&messages, NULL, 0, 0)) {
		TranslateMessage(&messages);
		DispatchMessage(&messages);
		Sleep(0.1f);
	}
}



void CALLBACK Menu::Init(HMODULE hmodule){
	Menu::CreateConsole();
	Menu::MainTimerLoop(hmodule);
}


using boost::system::error_code;
boost::asio::io_service io_service;
tcp::resolver resolver(io_service);
tcp::resolver::query query("192.168.1.100", "8081");
tcp::resolver::iterator i = resolver.resolve(query);
BoostLineClient client(io_service, i);


void CALLBACK Menu::MainTimerLoop(HMODULE hModule) {
	while (1) {
		if (!MemReader::GetInstance().IsOnline()) return;
		
		Menu::DisplayMenu(hModule);
		

		if (Util::isNotExhausted(Menu::socketLoop, 10))
		{
			
			if (Menu::shoot && Util::isNotExhausted(Menu::test, 2000)) {
				ComboRune::GetInstance().CastRune(Menu::RUNEID, Menu::targetId);
			}
			
		}

		if (Util::isNotExhausted(Menu::combo, 50)) {
			Menu::shoot = false;
			client.invokeRead();

			std::stringstream ss;
			ss.str(client.read_msg_.data());
			std::string s = ss.str();
			if (s.length() != 0) {
				Menu::shoot = true;
			}
			sscanf_s(client.read_msg_.data(), "%d", &Menu::targetId);
			client.read_msg_.setDataToEmpty();
		}
	}
}











void Menu::CreateConsole()
{
	if (!AllocConsole())
	{
		char buffer[1024] = { 0 };
		sprintf_s(buffer, "Failed to AllocConsole( ), GetLastError( ) = %d", GetLastError());
		MessageBox(HWND_DESKTOP, buffer, "Error", MB_OK);

		return;
	}

	auto lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	auto hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), _O_TEXT);
	auto fp = _fdopen(hConHandle, "w");

	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);

	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
}

void Menu::BodyMenu() {
	system("cls");
	system("Color 3");
	std::cout << R"(   _____                _           ____        _   
  / ____|              | |         |  _ \      | |  
 | |     ___  _ __ ___ | |__   ___ | |_) | ___ | |_ 
 | |    / _ \| '_ ` _ \| '_ \ / _ \|  _ < / _ \| __|
 | |___| (_) | | | | | | |_) | (_) | |_) | (_) | |_ 
  \_____\___/|_| |_| |_|_.__/ \___/|____/ \___/ \__|)" << std::endl;
	std::cout << "===================TEAMMATE MODE===================" << std::endl;
	printf("F1- Set Rune ID\n");
	printf("F2- Set Rune Delay\n");
	printf("F10- Eject dll\n");
	printf("F12- Menu information\n");
	if (Menu::RUNEID != 0 && Menu::RUNEDELAY != 0) {
		isRuneAndDelaySet = true;
		std::cout << "[Rune ID]: " << Menu::RUNEID << "\n";
		std::cout << "[Rune DELAY]: " << Menu::RUNEDELAY << "\n";
	}
}

void Menu::DisplayMenu(HMODULE hModule) {
	if (GetAsyncKeyState(VK_F12) & 1)
	{
		Menu::BodyMenu();
	}

	if (GetAsyncKeyState(VK_F1) & 1) {
		system("Color 3");
		Menu::RUNEID = 0;
		do {
			system("cls");
			std::cout << "Enter rune ID: ";
			std::cin >> Menu::RUNEID;
		} while (!std::cin);

		std::cout << "You have successfully set rune ID on: " << Menu::RUNEID << std::endl;
		std::cout << "Press F12 to display menu.";
	}



	if (GetAsyncKeyState(VK_F2) & 1) {
		system("Color 3");
		Menu::RUNEID = 0;
		do {
			system("cls");
			std::cout << "Enter rune Delay: ";
			std::cin >> Menu::RUNEDELAY;
		} while (!std::cin);

		std::cout << "You have successfully set delay on: " << Menu::RUNEID << std::endl;
		std::cout << "Press F12 to display menu.";
	}







	if (GetAsyncKeyState(VK_F10) & 1) {
		EjectDLL(reinterpret_cast<HMODULE>(hModule));
	}
}

void Menu::EjectDLL(HMODULE hModule)
{
	system("Color 3");
	system("cls");
	std::cout << "You can close the console window now." << std::endl;
	Sleep(500);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);

};