#pragma once
#include <vector>

#include "Entity/Entity.h"

class Scene {
public:
	Scene();
	~Scene();

	void addEntity(Entity* e);
	void removeEntity(Entity* e);

	std::vector<Entity*> getEntities();

	void simulate();
	void render();

private:
	std::vector<Entity*> entities;	//entities in the scene

};