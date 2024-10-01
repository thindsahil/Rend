#include "Program.h"

Program::Program()
{
	window = new Window(800, 800);
	int a = 1;
}

Program::~Program()
{
}


void Program:: start()
{
	while (isRunning) {
		if (!window->ProcessMessages()) {
			std::cout << "CLOSING WINDOW.\n";
			isRunning = false;
		}


	}
}
