#pragma once

namespace Menu {
	void CALLBACK Init(HMODULE hModule);
	void HandleMsgs();
	void CALLBACK MainTimerLoop(HMODULE hModule);
	void CreateConsole();
	void DisplayMenu(HMODULE hModule);
	void BodyMenu();
	void EjectDLL(HMODULE hModule);
	int ValidateIpV4(std::string ip);




	static MSG messages;
	static int32_t RUNEID = 3155;
	static int32_t RUNEDELAY = 2000;
	static bool isRuneAndDelaySet = false;
	static int32_t socketLoop;
	static int32_t test;
	static bool shotExecuted = false;

}


