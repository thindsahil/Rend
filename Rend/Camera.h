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
	Vec3F up;

	float fov;
	float nearPlane;
	float farPlane;
	float aspectRatio;

	int width;
	int height;

};
#endif // !CAMERA_H