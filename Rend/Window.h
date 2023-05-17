#include <Windows.h>
#include <stdint.h>
#include "Frame.h"



class Window {

public:
     Window(int width, int height);
     Window(const Window&) = delete;
     Window& operator =(const Window&) = delete;
     ~Window();
     
     bool ProcessMessages();

     void Render();
     void ProcessKeyboardInput();
     FRAMEBITMAP& GetFrameBuffer();
private:
     const int WIDTH;
     const int HEIGHT;
     const int FRAME_MEMORY_SIZE;

     HINSTANCE m_hInstance;
     HWND m_hWnd;
     FRAMEBITMAP frameBuffer = {0};

     static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
     void SetupFrameBuffer();
};