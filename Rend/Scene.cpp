#include "Scene.h"

Scene::Scene()
    :light(2,1,2)
{
    zBuffer = new float[width* height];
    light.normalize();
}

Scene::~Scene()
{
    delete[] zBuffer;

    for (auto e : entities) {
        delete e;
    }
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

void Scene::draw(Camera& camera, FRAMEBITMAP& frame)
{
    //  reset Z-Buffer
    std::fill_n(zBuffer, width * height, std::numeric_limits<float>::lowest());

    for (Entity* e : entities) {
        //e->rotateX(PI / 2);
        //std::cout <<"blah: " << (*e).vertices.size();
        for (int i = 0; i < (*e).vertices.size(); i += 3) {
            Vec3F triangle[3];
            Vec3F t[3];
            for (int j = 0; j < 3; j++) {
                Vec4F V = Vec4F((*e).vertices[i + j].pos, 1.0);
                Vec4F temp = rotateY(PI / 100) * V;
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

            //  colour of face based on light direction
            float in = dot(light , n);

            if (in > 0) {
                DrawTriangleZ3(triangle, zBuffer, frame, COLOR32(in * 0xFF, in * 0xFF, in * 0xFF, 0xFF));
            }

        }

    }
}
