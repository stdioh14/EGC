#include <string>
#include "Transform2D.h"
#include <Core/Engine.h>
#include "BowString.h"

#define MAX_FORCE 0.6f

Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}


BowString::BowString() {
	bowSMesh = CreateSquare("square2", glm::vec3(0, 0, 0), 100, glm::vec3(25, 25, 25), true);;
	model1 = glm::mat3(1);
	model2 = glm::mat3(1);
	force = 0;
}

BowString::~BowString() {}

Mesh* BowString::getMesh() {
	return bowSMesh;
}

float BowString::getForce(){
	return force;
}

glm::mat3 BowString::getModel1(glm::mat3 bow_model, float deltaT,bool pm1, bool rm1) {
	if (!pm1) {
		force = 0;
		model1 = bow_model * Transform2D::Translate(70, 0) * Transform2D::Scale(0.01f, 0.7);
	}
	else {
		force += deltaT/ 4;
		if (force > MAX_FORCE) force = MAX_FORCE;
		model1 = bow_model * Transform2D::Translate(70 - 70 * force, 0) * Transform2D::ForfecareY(force) * Transform2D::Scale(0.01f, 0.7);
	}
	return model1;
}

glm::mat3 BowString::getModel2(glm::mat3 bow_model, float deltaT, bool pm1, bool rm1) {
	if (!pm1) {
		model2 = bow_model * Transform2D::Scale(1, -1) * Transform2D::Translate(70, 0) * Transform2D::Scale(0.01f, 0.7);
		force = 0;
	}
	else {
		force += deltaT/4;
		if (force > MAX_FORCE) force = MAX_FORCE;
		model2 = bow_model * Transform2D::Scale(1, -1) * Transform2D::Translate(70 - 70 * force, 0) * Transform2D::ForfecareY(force) * Transform2D::Scale(0.01f, 0.7);
	}
	return model2;
}
