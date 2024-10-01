#ifndef CAMERA_H
#define CAMERA_H

#include "VecMath.h"

class Camera {
public:
	Camera();
	~Camera();

	Mat4F getViewMatrix();
	Mat4F getProjectionMatrix();
	Mat4F getViewportMatrix();

private:
	Vec3F position;
	Vec3F orientation;
	//Vec3F up;

	float fov;
	float zNear;
	float zFar;
	float aspectRatio;

	int width;
	int height;

};

//void processCameraControls(Mat4F& viewMat) {
//    if (GetAsyncKeyState(VK_UP)) {
//        std::cout << "UP presesd\n";
//        //eye.y += 0.1;
//        viewMat[1][3] -= 0.1;
//    }
//    if (GetAsyncKeyState(VK_DOWN)) {
//        std::cout << "Down presesd\n";
//        //eye.y -= 0.1;
//        viewMat[1][3] += 0.1;
//    }
//    if (GetAsyncKeyState(VK_LEFT)) {
//        std::cout << "UP presesd\n";
//        //eye.y += 0.1;
//        viewMat[0][3] += 0.1;
//    }
//    if (GetAsyncKeyState(VK_RIGHT)) {
//        std::cout << "Down presesd\n";
//        //eye.y -= 0.1;
//        viewMat[0][3] -= 0.1;
//    }
//}
#endif // !CAMERA_H