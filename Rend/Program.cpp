#include "Program.h"

Program::Program() 
	:isRunning(true)

{
	window = new Window(WIDTH, HEIGHT);
	Entity* model = new Model("../../../../obj/teapot.obj");
	model->rotateX(PI / 2);
	scene.addEntity(model);
}

Program::~Program()
{
	delete window;
	//delete model;
}


void Program:: start()
{
	const COLOR32 BLACK = { 0,0,0, 0xff };
	FRAMEBITMAP frame = window->GetFrameBuffer();
	while (isRunning) {

		if (!window->ProcessMessages()) {
			std::cout << "CLOSING WINDOW.\n";
			isRunning = false;
		}

		scene.draw(camera, frame);

		window->Render();
		// clear the screen
		FillRect(0, 0, WIDTH, HEIGHT, frame, BLACK);
		Sleep(1);

	}
}
