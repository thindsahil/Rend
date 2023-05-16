#define UNICODE
#include "Window.h"


LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
     switch(uMsg) {
          case WM_CLOSE: 
               DestroyWindow(hWnd); 
               break;
          case WM_DESTROY:
               PostQuitMessage(0);
               return 0;
     }
     return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window(int width, int height)
     : m_hInstance(GetModuleHandle(nullptr)),
       WIDTH(width),
       HEIGHT(height),
       FRAME_MEMORY_SIZE(width*height * sizeof(PIXEL32))
{
     
     const wchar_t* CLASS_NAME = L"Window Class";
     WNDCLASS wndClass = {};
     wndClass.lpszClassName = CLASS_NAME;
     wndClass.hInstance = m_hInstance;
     wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
     wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
     wndClass.hbrBackground = CreateSolidBrush(RGB(255,0,255));
     wndClass.lpfnWndProc = WindowProc; 
     RegisterClass(&wndClass);
     DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

     RECT rect;
     rect.left = 250;
     rect.top = 250;
     rect.right = rect.left + width;
     rect.bottom = rect.top + height;

     AdjustWindowRect(&rect, style, false);

     m_hWnd = CreateWindowEx(
               0,
               CLASS_NAME,
               L"Title",
               style,
               rect.left,
               rect.top,
               rect.right - rect.left,
               rect.bottom - rect.top,
               NULL,
               NULL,
               m_hInstance,
               NULL
     );
     SetupFrameBuffer();
     ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window() {
     //delete frame buffer
     VirtualFree(frameBuffer.pixels, 0, MEM_RELEASE);
     const wchar_t* CLASS_NAME = L"Window Class";
     UnregisterClass(CLASS_NAME, m_hInstance);
}

void Window::SetupFrameBuffer() {
     frameBuffer.BitmapInfo.bmiHeader.biSize = sizeof(frameBuffer.BitmapInfo.bmiHeader);
     frameBuffer.BitmapInfo.bmiHeader.biWidth = WIDTH;
     frameBuffer.BitmapInfo.bmiHeader.biHeight = HEIGHT;
     frameBuffer.BitmapInfo.bmiHeader.biBitCount = 32;
     frameBuffer.BitmapInfo.bmiHeader.biCompression = BI_RGB;
     frameBuffer.BitmapInfo.bmiHeader.biPlanes = 1;

     frameBuffer.pixels = VirtualAlloc(NULL, FRAME_MEMORY_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

}


bool Window::ProcessMessages() {
     MSG msg = {};
     
     while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
          if (msg.message == WM_QUIT) {
               return false;
          }   
          TranslateMessage(&msg);  
          DispatchMessage(&msg);
     }
     
     return true;
}


void Window::Render() {
    HDC deviceContext = GetDC(m_hWnd);
    StretchDIBits(deviceContext, 0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, frameBuffer.pixels, &frameBuffer.BitmapInfo, DIB_RGB_COLORS, SRCCOPY);

    ReleaseDC(m_hWnd, deviceContext);
}


void Window::ProcessKeyboardInput() {
     short escapeDown = GetAsyncKeyState(VK_ESCAPE);

     if (escapeDown) {
          PostMessage(m_hWnd, WM_CLOSE, 0,0);
     }
}

FRAMEBITMAP& Window::GetFrameBuffer()
{
    return frameBuffer;
}
