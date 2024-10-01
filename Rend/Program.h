#ifndef PROGRAM_H
#define PROGRAM_H

#include "Window.h"
#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"


class Program {
public:
	Program();
	~Program();

	void start();

private:
	Window* window;
	Scene scene;
	Camera camera;
	Renderer renderer;
	// Camera?

	bool isRunning;
};

#endif