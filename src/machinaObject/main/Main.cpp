#include "Main.hpp"

#include <string>

#include <Windows.h>

#include "logger.hpp"

Main::Main() {}

struct KeyBoardState {
	bool ESCAPE = 0;
	bool a = 0;

	void update() {
		ESCAPE = GetAsyncKeyState(VK_ESCAPE) & 0x0001;
		a = GetAsyncKeyState(0x41) & 0x0001;
	}

	void activeState() {
		// https://stackoverflow.com/questions/19059157/iterate-through-struct-and-class-members
		// issue to emplace keyboard
	}
};

void Main::fakeLoop() {
	KeyBoardState KBS{};

	while (true) {
		KBS.update();

		if (KBS.ESCAPE) {
			log("Ending loop ... ");
			break;
		}
		Sleep(REFRESH_TIME);
	}
}