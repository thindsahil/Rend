//#include <stdlib.h>
#include <iostream>
#include "Geometry.h"

typedef struct FRAMEBITMAP {
    BITMAPINFO BitmapInfo;
    void* pixels;
} FRAMEBITMAP;

typedef struct PIXEL32 {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
} PIXEL32;


inline void SetPixel(int x, int y, FRAMEBITMAP& frameBuffer, PIXEL32& color) {
    PIXEL32* coord = (PIXEL32*) frameBuffer.pixels + (frameBuffer.BitmapInfo.bmiHeader.biWidth * y) + x;
    memcpy_s(coord, sizeof(PIXEL32), &color, sizeof(PIXEL32));

}

inline void FillRect(int x, int y, int w, int h, FRAMEBITMAP& frameBuffer, PIXEL32& color) {
    for (int j = y; j < y+h; j++) {
        for (int i = x; i < x+w; i++) {
            PIXEL32* coord = (PIXEL32*)frameBuffer.pixels + (frameBuffer.BitmapInfo.bmiHeader.biWidth * j) + i;
            memcpy_s(coord, sizeof(PIXEL32), &color, sizeof(PIXEL32));
            //SetPixel(i, j, frameBuffer, color); 
        }
    }
}

inline void DrawLine(int x0, int y0, int x1, int y1, FRAMEBITMAP& frameBuffer, PIXEL32& color) {
    //  Cleanup later
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    bool flat = dx >= dy;

    if (flat) {
        // swap to draw from left to right
        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        float m = (y1 - y0) / (float)dx;
        int x = x0;
        int b = y0 - m * x0;
        while (x <= x1) {
            int y = round(m * x + b);
            SetPixel(x, y, frameBuffer, color);
            x++;
        }
    }
    else {
        if (y0 > y1) {
            std::swap(y0, y1);
            std::swap(x0, x1);
        }
        float m = (x1 - x0) / (float)dy;
        int b = x0 - m * y0;
        int y = y0;
        while (y <= y1) {
            int x = round(m * y + b);
            SetPixel(x, y, frameBuffer, color);
            y++;
        }

    }
}

inline void DrawLine(Vec2I a, Vec2I b,  FRAMEBITMAP& frameBuffer, PIXEL32& color) {
    DrawLine(a.x, a.y, b.x, b.y, frameBuffer, color);
}