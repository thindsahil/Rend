//#include <stdlib.h>

#ifndef FRAME_H
#define FRAME_H
#include <Windows.h>
#include <iostream>
#include <algorithm>
#include "VecMath.h"


typedef struct FRAMEBITMAP {
    BITMAPINFO BitmapInfo;
    void* pixels;
} FRAMEBITMAP;

typedef struct COLOR32 {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
    COLOR32(uint8_t b, uint8_t g, uint8_t r, uint8_t a) : blue(b), green(g), red(r), alpha(a) {};
} COLOR32;


inline void SetPixel(int x, int y, FRAMEBITMAP& frameBuffer, const COLOR32& color) {
    //TODO: add bounds
    if (x < 0 || y < 0) {
        //std::cout << "x: " << x << " y: " << y << "\n";
        return;

    }
    else if (x >= frameBuffer.BitmapInfo.bmiHeader.biWidth || y >= frameBuffer.BitmapInfo.bmiHeader.biHeight) {
        //std::cout << "x: " << x << " y: " << y << "\n";
        return;
    }

    COLOR32* coord = (COLOR32*)frameBuffer.pixels + (frameBuffer.BitmapInfo.bmiHeader.biWidth * y) + x;
    memcpy_s(coord, sizeof(COLOR32), &color, sizeof(COLOR32));


}

inline void FillRect(int x, int y, int w, int h, FRAMEBITMAP& frameBuffer,const  COLOR32& color) {
    //TODO: add bounds
    for (int j = y; j < y+h; j++) {
        for (int i = x; i < x+w; i++) {
            COLOR32* coord = (COLOR32*)frameBuffer.pixels + (frameBuffer.BitmapInfo.bmiHeader.biWidth * j) + i;
            memcpy_s(coord, sizeof(COLOR32), &color, sizeof(COLOR32));
            //SetPixel(i, j, frameBuffer, color); 
        }
    }
}

inline void DrawLine(int x0, int y0, int x1, int y1, FRAMEBITMAP& frameBuffer, const COLOR32& color) {
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
        int b = y0 - round(m * x0);
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

inline void DrawLine(Vec2I a, Vec2I b,  FRAMEBITMAP& frameBuffer, const COLOR32& color) {
    DrawLine(a.x, a.y, b.x, b.y, frameBuffer, color);
}

//  From https://gamedev.stackexchange.com/a/63203 
inline Vec3F barycentric2(Vec2I a, Vec2I b, Vec2I c, Vec2I p) {
    Vec2I v0 = b - a, v1 = c - a, v2 = p - a;
    int den = v0.x * v1.y - v1.x * v0.y;
    float v = (v2.x * v1.y - v1.x * v2.y) / (float) den;
    float w = (v0.x * v2.y - v2.x * v0.y) / (float) den;
    float u = 1.0f - v - w;
    return Vec3F(u, v, w);
}

inline Vec3F barycentric3(Vec3F a, Vec3F b, Vec3F c, Vec3F p) {
    Vec3F v0 = b - a, v1 = c - a, v2 = p - a;
    float den = v0.x * v1.y - v1.x * v0.y;
    float v = (v2.x * v1.y - v1.x * v2.y) / den;
    float w = (v0.x * v2.y - v2.x * v0.y) / den;
    float u = 1.0f - v - w;
    return Vec3F(u, v, w);
}


inline void DrawTriangle2(Vec2I a, Vec2I b, Vec2I c, FRAMEBITMAP& frameBuffer, const COLOR32& color) {
    //  Bounding box
    int xMin = std::min<int>({ a.x, b.x, c.x }); xMin = std::max<int>( 0, xMin );
    int xMax = std::max<int>({ a.x, b.x, c.x }); xMax = std::min<int>( frameBuffer.BitmapInfo.bmiHeader.biWidth - 1, xMax );
    int yMin = std::min<int>({ a.y, b.y, c.y }); yMin = std::max<int>( 0, yMin );
    int yMax = std::max<int>({ a.y, b.y, c.y }); yMax = std::min<int>( frameBuffer.BitmapInfo.bmiHeader.biHeight - 1, yMax);

    for (int x = xMin; x <= xMax; x++) {
        for (int y = yMin; y <= yMax; y++) {
            Vec3F bc = barycentric2(a, b, c, Vec2I(x, y));
            if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            SetPixel(x, y, frameBuffer, color);
        }
    }
}

inline void DrawTriangleMesh(Vec3F* pts, FRAMEBITMAP& frameBuffer, const COLOR32& color) {
    DrawLine((int) pts[0].x, (int) pts[0].y, (int) pts[1].x, (int) pts[1].y, frameBuffer, color);
    DrawLine((int) pts[0].x, (int) pts[0].y, (int) pts[2].x, (int) pts[2].y, frameBuffer, color);
    DrawLine((int) pts[1].x, (int) pts[1].y, (int) pts[2].x, (int) pts[2].y, frameBuffer, color);
}


//  DrawTriangle with vertices in screen space
inline void DrawTriangle3(Vec3F* pts, FRAMEBITMAP& frameBuffer, const COLOR32& color) {
    //  Bounding box
    int xMin = std::min<float>({ pts[0].x, pts[1].x, pts[2].x }); xMin = std::max<float>(0, xMin);
    int xMax = std::max<float>({ pts[0].x, pts[1].x, pts[2].x }); xMax = std::min<float>(frameBuffer.BitmapInfo.bmiHeader.biWidth - 1, xMax);
    int yMin = std::min<float>({ pts[0].y, pts[1].y, pts[2].y }); yMin = std::max<float>(0, yMin);
    int yMax = std::max<float>({ pts[0].y, pts[1].y, pts[2].y }); yMax = std::min<float>(frameBuffer.BitmapInfo.bmiHeader.biHeight - 1, yMax);

    Vec3F P;
    for (P.x = xMin; P.x <= xMax; P.x++) {
        for (P.y = yMin; P.y <= yMax; P.y++) {
            Vec3F bcScreen = barycentric3(pts[0], pts[1], pts[2], P);
            if (bcScreen.x < 0 || bcScreen.y < 0 || bcScreen.z < 0) continue;
            SetPixel(P.x, P.y, frameBuffer, color);
        }
    }
}

//  DrawTriangle with vertices in screen space and z buffer
inline void DrawTriangleZ3(Vec3F* pts, float* zbuf, FRAMEBITMAP& frameBuffer, const COLOR32& color) {
    //  Bounding box
    int xMin = std::min<float>({ pts[0].x, pts[1].x, pts[2].x }); xMin = std::max<float>(0, xMin);
    int xMax = std::max<float>({ pts[0].x, pts[1].x, pts[2].x }); xMax = std::min<float>(frameBuffer.BitmapInfo.bmiHeader.biWidth - 1, xMax);
    int yMin = std::min<float>({ pts[0].y, pts[1].y, pts[2].y }); yMin = std::max<float>(0, yMin);
    int yMax = std::max<float>({ pts[0].y, pts[1].y, pts[2].y }); yMax = std::min<float>(frameBuffer.BitmapInfo.bmiHeader.biHeight - 1, yMax);

    Vec3F P;
    for (P.x = xMin; P.x <= xMax; P.x++) {
        for (P.y = yMin; P.y <= yMax; P.y++) {
            Vec3F bcScreen = barycentric3(pts[0], pts[1], pts[2], P);
            if (bcScreen.x < 0 || bcScreen.y < 0 || bcScreen.z < 0) continue;
            P.z = 0;
            P.z += (pts[0].z * bcScreen.x);
            P.z += (pts[1].z * bcScreen.y);
            P.z += (pts[2].z * bcScreen.z);
            //P.z = std::min<float>({pts[0].z,pts[1].z ,pts[2].z });
            if (zbuf[int(P.x + P.y * frameBuffer.BitmapInfo.bmiHeader.biWidth)] < P.z) {
                zbuf[int(P.x + P.y * frameBuffer.BitmapInfo.bmiHeader.biWidth)] = P.z;
                SetPixel(P.x, P.y, frameBuffer, color);
            }
        }
    }
}

#endif