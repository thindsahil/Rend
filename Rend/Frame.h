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
    //TODO: add bounds
    PIXEL32* coord = (PIXEL32*) frameBuffer.pixels + (frameBuffer.BitmapInfo.bmiHeader.biWidth * y) + x;
    memcpy_s(coord, sizeof(PIXEL32), &color, sizeof(PIXEL32));

}

inline void FillRect(int x, int y, int w, int h, FRAMEBITMAP& frameBuffer, PIXEL32& color) {
    //TODO: add bounds
    for (int j = y; j < y+h; j++) {
        for (int i = x; i < x+w; i++) {
            PIXEL32* coord = (PIXEL32*)frameBuffer.pixels + (frameBuffer.BitmapInfo.bmiHeader.biWidth * j) + i;
            memcpy_s(coord, sizeof(PIXEL32), &color, sizeof(PIXEL32));
            //SetPixel(i, j, frameBuffer, color); 
        }
    }
}

inline void DrawLine(int x0, int y0, int x1, int y1, FRAMEBITMAP& frameBuffer, PIXEL32& color) {
    //TODO:  Cleanup later and add bounds
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

//  From https://gamedev.stackexchange.com/a/63203 
inline Vec3F barycentric(Vec2I a, Vec2I b, Vec2I c, Vec2I p) {
    Vec2I v0 = b - a, v1 = c - a, v2 = p - a;
    int den = v0.x * v1.y - v1.x * v0.y;
    float v = (v2.x * v1.y - v1.x * v2.y) / (float) den;
    float w = (v0.x * v2.y - v2.x * v0.y) / (float) den;
    float u = 1.0f - v - w;
    return Vec3F(u, v, w);
}

inline void DrawTriangle(Vec2I a, Vec2I b, Vec2I c, FRAMEBITMAP& frameBuffer, PIXEL32& color) {
    //  Bounding box
    int xMin = min(a.x, b.x, c.x); xMin  = max(0, xMin);
    int xMax = max(a.x, b.x, c.x); xMax = min(frameBuffer.BitmapInfo.bmiHeader.biWidth - 1, xMax);
    int yMin = min(a.y, b.y, c.y); yMin = max(0, yMin);
    int yMax = max(a.y, b.y, c.y); yMax = min(frameBuffer.BitmapInfo.bmiHeader.biHeight - 1, yMax);

    for (int x = xMin; x <= xMax; x++) {
        for (int y = yMin; y <= yMax; y++) {
            Vec3F bc = barycentric(a, b, c, Vec2I(x, y));
            if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            SetPixel(x, y, frameBuffer, color);
        }
    }
}