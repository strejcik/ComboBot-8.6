#pragma once

namespace Menu {
	void CALLBACK Init(HMODULE hModule);
	void HandleMsgs();
	void CALLBACK MainTimerLoop(HMODULE hModule);
	void CreateConsole();
	void DisplayMenu(HMODULE hModule);
	void BodyMenu();
	void EjectDLL(HMODULE hModule);




	static MSG messages;
	static int PORT = 0;
	static std::string IPSTRING = "127.0.0.1";
	static int32_t RUNEID = 3174;
	static int32_t RUNEDELAY = 2000;
	static bool isRuneAndDelaySet = false;
	static int32_t socketLoop;
	static int32_t test;
	static int32_t combo;
	static int32_t targetId;
	static bool shoot = false;


	
}


