#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Sky.h"

Mesh* createSky() {
	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};

	Mesh* sq = new Mesh("Square");

	vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.52f, 0.80f, 0.92)));
	vertices.push_back(VertexFormat(glm::vec3(0, 100, 0), glm::vec3(0.52f, 0.80f, 0.92)));
	vertices.push_back(VertexFormat(glm::vec3(100, 0, 0), glm::vec3(0.52f, 0.80f, 0.92)));
	vertices.push_back(VertexFormat(glm::vec3(100, 100, 0), glm::vec3(0.52f, 0.80f, 0.92)));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	sq->InitFromData(vertices, indices);
	return sq;

}

Sky::Sky() {
	skyM = createSky();
}

Sky::~Sky() {}

Mesh* Sky::getMesh() {
	return skyM;
}

glm::mat3 Sky::getModel() {
	return Transform2D::Scale(100, 100);
}