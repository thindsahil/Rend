#include <iostream>
#include "Window.h"



int main(int argc, char* argv[])
{   
    std::cout << "creating window...\n";
    Window* pWindow = new Window(800, 600);
    FRAMEBITMAP frame = pWindow->GetFrameBuffer();
    PIXEL32 red = { 0,0,0xff, 0xff };
    FillRect(300, 100, 20, 20, frame, red);
    DrawLine(Vec2I(600, 300), Vec2I(20, 30), frame, red);
    bool running = true;

    while (running) {
        if (!pWindow->ProcessMessages()) {
            std::cout << "closing window\n";
            running = false;
        }
        // pWindow->ProcessKeyboardInput();
        pWindow->Render();
        Sleep(1);
    }

    delete pWindow;
    return 0;
}