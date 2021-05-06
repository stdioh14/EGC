#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "PowerBar.h"

Mesh* createBar() {
	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};

	Mesh* sq = new Mesh("Square");

	vertices.push_back(VertexFormat(glm::vec3(-5, -50, 0), glm::vec3(1, 0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-5, 50, 0), glm::vec3(1, 0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(5, -50, 0), glm::vec3(1, 0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(5, 50, 0), glm::vec3(1, 0, 0)));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	sq->InitFromData(vertices, indices);
	return sq;

}

PowerBar::PowerBar() {
	pbM = createBar();
	modelMatrix = glm::mat3(1);
}

PowerBar::~PowerBar() {}

Mesh* PowerBar::getMesh() {
	return pbM;
}

glm::mat3 PowerBar::getModel(float force, glm::vec3 position) {
	return Transform2D::Translate(40, position.y) * Transform2D::Scale(1, force / 0.6f);
}