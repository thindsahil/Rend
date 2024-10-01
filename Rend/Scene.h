#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Entity/Entity.h"
#include "Camera.h"
#include "Frame.h"
#include "VecMath.h"

class Scene {
public:
	Scene();
	~Scene();

	void addEntity(Entity* e);
	void removeEntity(Entity* e);

	void draw(Camera& camera, FRAMEBITMAP& frame);


private:
    float* zBuffer;
    
    int width = 800;
    int height = 600;

    Vec3F light; // 1 light for now

	std::vector<Entity*> entities;	//entities in the scene

	// rotation matrices
    Mat4F rotateX(float xAngleRad) {
        Mat4F rot;
        rot[0][0] = 1.0f;
        rot[1][1] = cosf(xAngleRad);
        rot[1][2] = -sinf(xAngleRad);
        rot[2][1] = sin(xAngleRad);
        rot[2][2] = cosf(xAngleRad);
        rot[3][3] = 1.0f;

        return rot;

    }

    Mat4F rotateY(float yAngleRad) {
        Mat4F rot;
        rot[0][0] = cosf(yAngleRad);
        rot[0][2] = sinf(yAngleRad);
        rot[1][1] = 1.0f;
        rot[2][0] = -sinf(yAngleRad);
        rot[2][2] = cosf(yAngleRad);
        rot[3][3] = 1.0;
        return rot;
    }

    Mat4F rotateZ(float rotAngleRad) {
        Mat4F rot;
        rot[0][0] = cosf(rotAngleRad);
        rot[0][1] = -sinf(rotAngleRad);
        rot[1][0] = sinf(rotAngleRad);
        rot[1][1] = cosf(rotAngleRad);
        rot[2][2] = 1.0f;
        rot[3][3] = 1.0f;
        return rot;
    }

};

#endif // !SCENE_H