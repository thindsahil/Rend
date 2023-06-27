#include "Model.h"

Model::Model(const char* filePath)
{
	ObjLoader loader = ObjLoader();
	
	ObjModel mOBJ = loader.load(filePath);
	if (!mOBJ.valid) throw std::invalid_argument("Invalid OBJ, problem likely caused by bad filePath");
	this->vertices.assign(mOBJ.vertices.begin(), mOBJ.vertices.end());
}

Model::~Model()
{
}
