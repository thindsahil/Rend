#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Geometry.h"

struct Vertex {
	Vec3F pos;
	Vec2F UV;
	Vec3F normal;
};

typedef std::vector<Vertex> Vertices;

struct Model {
	bool valid;
	std::vector<Vertex> vertices;
};

//static void debugVertexPositions(Vec3F& positions) {
//	std::cout.precision(6);
//	std::cout << "v" << " " << std::fixed << positions.x << " " << positions.y << " " << positions.z << "\n";
//	
//}

//static void debugVertices(Vertices& v) {
//	for (int i = 0; i < v.size(); i++) {
//		debugVertexPositions(v[i].pos);
//	}
//}

class ObjLoader{
public:
	ObjLoader(){};
	~ObjLoader(){};

	Model load(const char* fileName) {
		std::vector<Vec3F> vertexPositions;
		std::vector<Vec2F> vertexUVs;
		std::vector<Vec3F> vertexNormals;

		std::vector< unsigned int > posIndices, uvIndices, normalIndices;

		std::stringstream ss;
		std::ifstream inFile(fileName);

		std::string line = "";
		std::string prefix = "";

		Vec3F tempV3;
		Vec2F tempV2;
		unsigned int tempInt;

		Model model = {0};
		model.valid = false;

		if (!inFile.is_open()) return model;
		while (std::getline(inFile, line)) {
			ss.clear();
			ss.str(line);
			prefix = "";
			ss >> prefix;

			if (prefix == "v") {
				ss >> tempV3.x >> tempV3.y >> tempV3.z;
				vertexPositions.push_back(tempV3);
			}
			else if (prefix == "vt") {
				ss >> tempV2.x >> tempV2.y;
				vertexUVs.push_back(tempV2);
			}
			else if (prefix == "vn") {
				ss >> tempV3.x >> tempV3.y >> tempV3.z;
				vertexNormals.push_back(tempV3);
			}
			else if (prefix == "f") {
				int counter = 0;
				while (ss >> tempInt) {
					if (counter == 0) {
						posIndices.push_back(tempInt);
					}
					else if (counter == 1) uvIndices.push_back(tempInt);
					else if (counter == 2) normalIndices.push_back(tempInt);

					if (ss.peek() == '/') {
						counter++;
						ss.ignore(1, '/');

					}
					else if (ss.peek() == ' ') {
						counter++;
						ss.ignore(1, ' ');
					}

					if (counter > 2) {
						counter = 0;
					}
				}
			}
			else {
				//	Maybe needed
			}

		}

		//	Build Mesh
		model.vertices.resize(posIndices.size(), Vertex());
		for (unsigned int i = 0; i < model.vertices.size(); i++) {
			model.vertices[i].pos = vertexPositions[posIndices[i] - 1];
			model.vertices[i].UV = vertexUVs[uvIndices[i] - 1];
			model.vertices[i].normal = vertexNormals[normalIndices[i] - 1];
		}
		model.valid = true;
		return model;
	}
private:


};

