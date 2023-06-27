#include "Scene.h"

Scene::Scene()
{

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

void Scene::simulate()
{
}

void Scene::render()
{
}
