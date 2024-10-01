#include "Scene.h"

Scene::Scene()
{
    return;
}

Scene::~Scene()
{
}

void Scene::addEntity(Entity* e)
{
	this->entities.push_back(e);
}

void Scene::removeEntity(Entity* e)
{
	auto index = std::find(this->entities.begin(), this->entities.end(), e);
	if (index != this->entities.end()) {
		this->entities.erase(index);
	}
	else {
		//	add something to indicate entity not in scene
	}

}

std::vector<Entity*> Scene::getEntities()
{
	return this->entities;
}

void Scene::render(Camera& camera, FRAMEBITMAP& frame)
{
    for (auto e : entities) {
        for (int i = 0; i < (*e).vertices.size(); i += 3) {
            Vec3F triangle[3];
            Vec3F t[3];
            for (int j = 0; j < 3; j++) {
                Vec4F V = Vec4F((*e).vertices[i + j].pos, 1.0);
                Vec4F temp = rotateY(PI / 2) * V;
                (*e).vertices[i + j].pos = Vec3F(temp.x, temp.y, temp.z);

                V = camera.getProjectionMatrix() * camera.getViewMatrix() * temp;

                V.x = (V.x / V.w);
                V.y = (V.y / V.w);
                V.z = (V.z / V.w);
                V.w = (V.w / V.w);

                t[j] = Vec3F(V.x, V.y, V.z);
                V = camera.getViewportMatrix() * V;
                triangle[j] = Vec3F(V.x, V.y, V.z);

            }

            Vec3F n = cross(t[2] - t[0], t[1] - t[0]);
            n.normalize();

            //  colour of face
            float in = dot(light, n);

            if (in > 0) {
                DrawTriangleZ3(triangle, zBuffer, frame, COLOR32(in * 0xFF, in * 0xFF, in * 0xFF, 0xFF));
            }

        }

    }
}
