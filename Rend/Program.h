#ifndef PROGRAM_H
#define PROGRAM_H

#include "Window.h"
#include "Scene.h"
#include "Camera.h"
#include "Entity/Model.h"


class Program {
public:
	Program();
	~Program();

	void start();

private:
	Window* window;
	Scene scene;
	Camera camera;
	// Camera?

	bool isRunning;

	int WIDTH = 800;
	int HEIGHT = 600;
};

#endif