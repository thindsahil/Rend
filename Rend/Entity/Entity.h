#pragma once
#include <vector>
#include "../VecMath.h"

class Entity {
public: 
	Entity();
	~Entity();

	std::vector<Vertex>& getVertices();
	void rotateX(float angle);
	void translate(float x, float y, float z);

	int numFaces();

	std::vector<Vertex> vertices;
};