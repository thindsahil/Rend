#ifndef WINDOW_H
#define WINDOW_H

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

     void PrintBitmapInfo(BITMAPINFO* bmi) {
         if (bmi == NULL) {
             printf("BITMAPINFO is NULL\n");
             return;
         }

         printf("BITMAPINFO:\n");
         printf("  biSize: %u\n", bmi->bmiHeader.biSize);
         printf("  biWidth: %d\n", bmi->bmiHeader.biWidth);
         printf("  biHeight: %d\n", bmi->bmiHeader.biHeight);
         printf("  biPlanes: %u\n", bmi->bmiHeader.biPlanes);
         printf("  biBitCount: %u\n", bmi->bmiHeader.biBitCount);
         printf("  biCompression: %u\n", bmi->bmiHeader.biCompression);
         printf("  biSizeImage: %u\n", bmi->bmiHeader.biSizeImage);
         printf("  biXPelsPerMeter: %d\n", bmi->bmiHeader.biXPelsPerMeter);
         printf("  biYPelsPerMeter: %d\n", bmi->bmiHeader.biYPelsPerMeter);
         printf("  biClrUsed: %u\n", bmi->bmiHeader.biClrUsed);
         printf("  biClrImportant: %u\n", bmi->bmiHeader.biClrImportant);

         if (bmi->bmiHeader.biBitCount <= 8) {
             printf("Color Palette:\n");
             for (int i = 0; i < (1 << bmi->bmiHeader.biBitCount); i++) {
                 printf("  Color[%d]: R=%u, G=%u, B=%u\n",
                     i,
                     bmi->bmiColors[i].rgbRed,
                     bmi->bmiColors[i].rgbGreen,
                     bmi->bmiColors[i].rgbBlue);
             }
         }
     }

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

#endif