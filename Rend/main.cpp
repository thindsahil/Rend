#include <iostream>
#include <stdlib.h>
#include <limits>

#include "Window.h"
#include "VecMath.h"
#include "Scene.h"
#include "Entity/Entity.h"
#include "Entity/Model.h"

#define WIDTH 800
#define HEIGHT 600

const COLOR32 RED = { 0,0,0xff, 0xff };
const COLOR32 BLACK = { 0,0,0, 0xff };
//float depth = 0xff;

COLOR32 randColor() {
    COLOR32 color(rand() % 0xFF, rand() % 0xFF, rand() & 0xFF, 0xFF);
    return color;

}

Mat4F makeViewportMat(int x, int y, int w, int h) {
    Mat4F v;
    v[0][3] = (x + w) / 2.f;
    v[1][3] = (y + h) / 2.f;
    v[2][3] = 0.5f;

    v[0][0] = (w - 1) / 2.f;
    v[1][1] = (h - 1) / 2.f;
    v[2][2] = 1.0f;
    v[3][3] = 1.0f;
    return v;
}

Mat4F makeViewMat(Vec3F eye, Vec3F target, Vec3F up) {
    Mat4F v;

    Vec3F k = (eye - target).normalize();
    Vec3F i = cross(up, k).normalize();
    Vec3F j = cross(k, i).normalize();

    v.setCol(Vec4F(i, 0.0), 0);
    v.setCol(Vec4F(j, 0.0), 1);
    v.setCol(Vec4F(k, 0.0), 2);
    v.setCol(Vec4F(eye, 1.0), 3);

    return v;
}


Mat4F makePerspectiveMat(float fovDeg, float aspectRatio, float zNear, float zFar) {
    Mat4F M;
    float fovRad = tanf(fovDeg * 0.5f * 3.14159f / 180);
    M[0][0] = 1/(aspectRatio * fovRad);  
    M[1][1] = 1 / fovRad;
    M[2][2] = -(zFar + zNear) / (zFar - zNear);
    M[3][2] = -1;
    M[2][3] = -(2 * zFar * zNear) / (zFar - zNear);
    return M;
}

Mat4F makeOrthographicMat(float left, float right, float top, float bottom, float fNear, float fFar) {
    Mat4F M;

    M[0][0] = 2.0f / (right - left);
    M[1][1] = 2.0f / (top - bottom);
    M[2][2] = -2.0f / (fFar - fNear);
    M[3][3] = 1.0f;

    M[0][3] = -(right + left) / (right - left);
    M[1][3] = -(top + bottom) / (top - bottom);
    M[2][3] = -(fFar + fNear) / (fFar - fNear);

    return M;
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

Vec3F lineIntersectPlane(Vec3F P, Vec3F planeNormal, Vec3F lineStart, Vec3F lineEnd) {

    planeNormal.normalize();
    float d = -dot(P, planeNormal);
    float ad = dot(lineStart, planeNormal);
    float bd = dot(lineEnd, planeNormal);
    float t = (-d - ad) / (bd - ad);

    Vec3F lineVec = lineEnd - lineStart;
    Vec3F intersect = lineVec * t;

    return lineVec + intersect;
    //return Vec3F();
}

void processCameraControls(Mat4F& viewMat) {
    if (GetAsyncKeyState(VK_UP)) {
        std::cout << "UP presesd\n";
        //eye.y += 0.1;
        viewMat[1][3] -= 0.1;
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        std::cout << "Down presesd\n";
        //eye.y -= 0.1;
        viewMat[1][3] += 0.1;
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        std::cout << "UP presesd\n";
        //eye.y += 0.1;
        viewMat[0][3] += 0.1;
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        std::cout << "Down presesd\n";
        //eye.y -= 0.1;
        viewMat[0][3] -= 0.1;
    }
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

    V2.normalize();
    std::cout << "Normailize:" << std::endl;
    std::cout << V2 << std::endl;

}

int main(int argc, char* argv[])
{   
    //test();
    //return 1;
    //std::cout << "creating window...\n";
    //std::cout << argv[0] << "\n";

    Window* pWindow = new Window(WIDTH, HEIGHT);
    FRAMEBITMAP frame = pWindow->GetFrameBuffer();

    Scene scene = Scene();
    Entity model = Model("../../../../obj/teapot.obj");
    scene.addEntity(&model);

    //Entity te = Model("../../../../obj/cube.obj");
    //scene.addEntity(&te);
    //te.translate(0, 0, -5);

    //  projection matrix
    float zNear = 0.1f;
    float zFar = 100.0f;
    float fov = 90.0f;
    float aspectRatio = (float)HEIGHT / WIDTH;
    Mat4F pProj = makePerspectiveMat(fov, aspectRatio, zNear, zFar);
    Mat4F oProj = makeOrthographicMat(-1.0, 1.0, -1.0, 1.0, 0.0, -10.0);

    // view matrix
    Vec3F eye(0, 0, 2);
    Vec3F target(0,0,0);
    Mat4F modelView = makeViewMat(eye, target, Vec3F(0, 1, 0));
    
    //viewport
    Mat4F viewport = makeViewportMat(0, 0, WIDTH, HEIGHT);

    //  rotation matrices
    float angle = 3.14159f;
    Mat4F rotX = makeRotX(angle/2);
    Mat4F rotY = makeRotY(angle/60);
    Mat4F rotZ = makeRotZ(angle/2);

    //  rotate teapot model
    model.rotateX(angle/2);

    //  light
    Vec3F light(2, 1, 3);
    light.normalize();

    //  z-buffer
    float* zBuf = new float[WIDTH * HEIGHT];

    std::cout << "nasdiasduas" << std::endl;
    std::cout << scene.getEntities().size() << std::endl;

    //return 0;

    bool running = true;
    while (running) {
        if (!pWindow->ProcessMessages()) {
            std::cout << "closing window\n";
            running = false;
        }
         //pWindow->ProcessKeyboardInput();
        processCameraControls(modelView);

        //  reset Z-Buffer
        std::fill_n(zBuf, WIDTH * HEIGHT, std::numeric_limits<float>::lowest());
        
        //  render entities in scene
        for (Entity* e : scene.getEntities()) {
            for (int i = 0; i < (*e).vertices.size(); i += 3) {
                Vec3F triangle[3];
                Vec3F t[3];
                for (int j = 0; j < 3; j++) {
                    Vec4F V = Vec4F((*e).vertices[i + j].pos, 1.0);
                    Vec4F temp = rotY * V;
                    (*e).vertices[i + j].pos = Vec3F(temp.x, temp.y, temp.z);

                    V = pProj * modelView * temp;

                    V.x = (V.x / V.w);
                    V.y = (V.y / V.w);
                    V.z = (V.z / V.w);
                    V.w = (V.w / V.w);

                    t[j] = Vec3F(V.x, V.y, V.z);
                    V = viewport * V;
                    triangle[j] = Vec3F(V.x, V.y, V.z);

                }

                Vec3F n = cross(t[2] - t[0], t[1] - t[0]);
                n.normalize();

                //  colour of face
                float in = dot(light, n);

                if (in > 0) {
                    DrawTriangleZ3(triangle, zBuf, frame, COLOR32(in * 0xFF, in * 0xFF, in * 0xFF, 0xFF));
                }

            }
        }

        pWindow->Render();
        Sleep(1);
        FillRect(0, 0, WIDTH, HEIGHT, frame, BLACK);

        //DrawLine()
    }
    delete[] zBuf;
    delete pWindow;
    return 0;
}