#include "Camera.h"

//Mat4F makeViewportMat(int x, int y, int w, int h) {
//    Mat4F v;
//    v[0][3] = (x + w) / 2.f;
//    v[1][3] = (y + h) / 2.f;
//    v[2][3] = 0.5f;
//
//    v[0][0] = (w - 1) / 2.f;
//    v[1][1] = (h - 1) / 2.f;
//    v[2][2] = 1.0f;
//    v[3][3] = 1.0f;
//    return v;
//}
//
//Mat4F makeViewMat(Vec3F eye, Vec3F target, Vec3F up) {
//    Mat4F v;
//
//    Vec3F k = (eye - target).normalize();
//    Vec3F i = cross(up, k).normalize();
//    Vec3F j = cross(k, i).normalize();
//
//    v.setCol(Vec4F(i, 0.0), 0);
//    v.setCol(Vec4F(j, 0.0), 1);
//    v.setCol(Vec4F(k, 0.0), 2);
//    v.setCol(Vec4F(eye, 1.0), 3);
//
//    return v;
//}
//
//
//Mat4F makePerspectiveMat(float fovDeg, float aspectRatio, float zNear, float zFar) {
//    Mat4F M;
//    float fovRad = tanf(fovDeg * 0.5f * 3.14159f / 180);
//    M[0][0] = 1 / (aspectRatio * fovRad);
//    M[1][1] = 1 / fovRad;
//    M[2][2] = -(zFar + zNear) / (zFar - zNear);
//    M[3][2] = -1;
//    M[2][3] = -(2 * zFar * zNear) / (zFar - zNear);
//    return M;
//}

//Mat4F makeOrthographicMat(float left, float right, float top, float bottom, float fNear, float fFar) {
//    Mat4F M;
//
//    M[0][0] = 2.0f / (right - left);
//    M[1][1] = 2.0f / (top - bottom);
//    M[2][2] = -2.0f / (fFar - fNear);
//    M[3][3] = 1.0f;
//
//    M[0][3] = -(right + left) / (right - left);
//    M[1][3] = -(top + bottom) / (top - bottom);
//    M[2][3] = -(fFar + fNear) / (fFar - fNear);
//
//    return M;
//}

Camera::Camera()
{
}

Camera::~Camera()
{
}

Mat4F Camera::getViewMatrix()
{
    return Mat4F();
}

Mat4F Camera::getProjectionMatrix()
{
    return Mat4F();
}

Mat4F Camera::getViewportMatrix()
{
    return Mat4F();
}
