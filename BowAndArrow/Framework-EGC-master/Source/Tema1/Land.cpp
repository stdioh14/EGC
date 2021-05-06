#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Land.h"


Mesh* createGrass() {
	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};

	Mesh* sq = new Mesh("Square");

	vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.25f, 0.59f, 0.04f)));
	vertices.push_back(VertexFormat(glm::vec3(0, 200, 0), glm::vec3(0.25f, 0.59f, 0.04f)));
	vertices.push_back(VertexFormat(glm::vec3(200, 0, 0), glm::vec3(0.25f, 0.59f, 0.04f)));
	vertices.push_back(VertexFormat(glm::vec3(200, 200, 0), glm::vec3(0.25f, 0.59f, 0.04f)));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	sq->InitFromData(vertices, indices);
	return sq;

}

Land::Land() {
	landM = createGrass();
}

Land::~Land() {}

Mesh* Land::getMesh() {
	return landM;
}

glm::mat3 Land::getModel() {
	return Transform2D::Scale(100, 1);
}