#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

std::vector<Vertex>& Entity::getVertices()
{
    return this->vertices;
}

void Entity::rotateX(float angle)
{
    //  hardcoded for now
    Mat4F rot;
    rot[0][0] = 1.0f;
    rot[1][1] = cosf(angle);
    rot[1][2] = -sinf(angle);
    rot[2][1] = sin(angle);
    rot[2][2] = cosf(angle);
    rot[3][3] = 1.0f;

    for (int i = 0; i < this->vertices.size(); i++) {
        Vec4F temp = Vec4F(this->vertices[i].pos, 1.0);
        temp = rot * temp;
        this->vertices[i].pos = Vec3F(temp.x, temp.y, temp.z);
    }
}

int Entity::numFaces()
{
    return this->vertices.size()/3;
}
