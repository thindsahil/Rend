#pragma once
#include <vector>
#include "../VecMath.h"

class Entity {
public: 
	Entity();
	~Entity();

	std::vector<Vertex>& getVertices();
	void rotateX(float angle);

	int numFaces();

	std::vector<Vertex> vertices;
};