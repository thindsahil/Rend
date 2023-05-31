﻿#include <iostream>
#include <stdlib.h>
#include <limits>
#include "Window.h"
#include "ObjLoader.h"

#define WIDTH 800
#define HEIGHT 600

const COLOR32 RED = { 0,0,0xff, 0xff };
const COLOR32 BLACK = { 0,0,0, 0xff };
float depth = 0xff;

COLOR32 randColor() {
    COLOR32 color(rand() % 0xFF, rand() % 0xFF, rand() & 0xFF, 0xFF);
    return color;

}

Mat4F makeViewportMat(int x, int y, int w, int h) {
    Mat4F v;
    v[0][3] = x + w / 2.f;
    v[1][3] = y + h / 2.f;
    v[2][3] = 10.0f / 2.f;

    v[0][0] = w / 2.f;
    v[1][1] = h / 2.f;
    v[2][2] = 10.0f / 2.f;
    v[3][3] = 1.0f;
    return v;
}

Mat4F makeViewMat(Vec3F eye, Vec3F target, Vec3F up) {
    Mat4F v;

    Vec3F k = (eye - target).normalize();
    Vec3F i = (up ^ k).normalize();
    Vec3F j = (k ^ i).normalize();

    v.setCol(Vec4F(i, 0.0), 0);
    v.setCol(Vec4F(j, 0.0), 1);
    v.setCol(Vec4F(k, 0.0), 2);
    v.setCol(Vec4F(eye, 1.0), 3);

    //v[0][0] = 1.0f;
    //v[1][1] = 1.0f;
    //v[2][2] = 1.0f;
    //v[3][3] = 1.0f;



    return v;
}

Mat4F makeProjectionMat(float fovDeg, float aspectRatio, float fNear, float fFar) {
    Mat4F projection;

    float fovRad = 1.0f / tanf(fovDeg * 0.5f * 3.14159f / 180);
    projection[0][0] = aspectRatio * fovRad;
    projection[1][1] = fovRad;
    projection[2][2] = -(fFar + fNear) / (fFar - fNear);
    projection[3][2] = (-2*fFar * fNear) / (fFar - fNear);
    projection[2][3] = -1.0f;
    projection[3][3] = 0.0f;
    return projection;
}

Mat4F makeRotX(float xAngleRad) {
    Mat4F rot;
    rot[0][0] = 1.0f;
    rot[1][1] = cosf(xAngleRad);
    rot[1][2] = -sinf(xAngleRad);
    rot[2][1] = sin(xAngleRad);
    rot[2][2] = cosf(xAngleRad);
    rot[3][3] = 1.0f;

    return rot;

}

Mat4F makeRotY(float yAngleRad) {
    Mat4F rot;
    rot[0][0] = cosf(yAngleRad);
    rot[0][2] = sinf(yAngleRad);
    rot[1][1] = 1.0f;
    rot[2][0] = -sinf(yAngleRad);
    rot[2][2] = cosf(yAngleRad);
    rot[3][3] = 1.0;
    return rot;
}

Mat4F makeRotZ(float rotAngleRad) {
    Mat4F rot;
    rot[0][0] = cosf(rotAngleRad);
    rot[0][1] = -sinf(rotAngleRad);
    rot[1][0] = sinf(rotAngleRad);
    rot[1][1] = cosf(rotAngleRad);
    rot[2][2] = 1.0f;
    rot[3][3] = 1.0f;
    return rot;
}


void test() {

    Mat3F M = { {0, 1, 2},
                {2, 3, 4},
                {5, 6, 7} }; 

    Vec3F V(1,2,3);
    std::cout << "===3x3 matrix-matrix multiplication===" << std::endl;
    std::cout << M * M << std::endl;

    std::cout << "===3x3 matrix-vector multiplication===" << std::endl;
    std::cout << M * V << std::endl;

    Mat4F M2 = { {1,2,3,4}, {2,3,4,5}, {1,4,2,6}, {1,2,9,6} };
    Vec4F V2(2, 4, 6, 7);
    std::cout << "===4x4 matrix-matrix multiplication===" << std::endl;
    std::cout << M2 * M2 << std::endl;

    std::cout << "===4x4 matrix-vector multiplication===" << std::endl;
    std::cout << M2 * V2 << std::endl;

    std::cout << "2nd column vector: " << M2.col(2) << std::endl;
    M2.setCol(Vec4F(9, 9, 9, 9), 3);
    std::cout << "2nd column changed:\n" << M2 << std::endl;

}

int main(int argc, char* argv[])
{   
    //test();

    std::cout << "creating window...\n";
    std::cout << argv[0] << "\n";
    Window* pWindow = new Window(WIDTH, HEIGHT);
    FRAMEBITMAP frame = pWindow->GetFrameBuffer();

    ObjLoader loader = ObjLoader();
    Model model = loader.load("../../../../obj/teapot.obj");
    if (model.valid) {
        std::cout << "# of vertices: " << model.vertices.size() << "\n";
    }
    //  projection matrix
    float fNear = 0.1f;
    float fFar = 10.0f;
    float fFov = 90.0f;
    float fAspectRatio = (float)HEIGHT / WIDTH;
    Mat4F proj = makeProjectionMat(fFov, fAspectRatio, fNear, fFar);

    // view matrix
    Vec3F eye(2, 1, 1);
    Vec3F target(0,1,1);
    Mat4F modelView = makeViewMat(eye, target, Vec3F(1, 1, 1));
    
    //viewport
    Mat4F viewport = makeViewportMat(0, 0, WIDTH, HEIGHT);

    bool running = true;

    float angle = 0.5f;
    Mat4F rotX = makeRotX(angle);
    Mat4F rotY = makeRotY(angle);
    Mat4F rotZ = makeRotZ(angle);

    while (running) {
        if (!pWindow->ProcessMessages()) {
            std::cout << "closing window\n";
            running = false;
        }
        // pWindow->ProcessKeyboardInput();

        for (int i = 0; i < model.vertices.size(); i += 3) {
            Vec3F triangle[3];
            for (int j = 0; j < 3; j++) {
                Vec4F temp = Vec4F(model.vertices[i + j].pos, 1.0);
                Vec4F rotV = rotZ * temp;
                model.vertices[i + j].pos = Vec3F(rotV.x, rotV.y, rotV.z);

                temp = viewport * proj * modelView * rotY * rotV;
                //temp = viewport * temp;
                triangle[j] = Vec3F(temp.x, temp.y, temp.z);

            }
            DrawTriangleSC(triangle,frame, COLOR32(i/3,0,0, 0xFF));

        }

        pWindow->Render();
        Sleep(100);
        FillRect(0, 0, WIDTH, HEIGHT, frame, BLACK);
    }

    delete pWindow;
    return 0;
}