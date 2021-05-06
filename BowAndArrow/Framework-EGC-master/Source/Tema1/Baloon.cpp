#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Baloon.h"

Mesh* CreateBaloon(std::string name, glm::vec3 color)
{

	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};


	Mesh* baloon = new Mesh(name);

	int n = 100;
	float angle, x, y;
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));
	for (int i = 0; i <= n; i++) {
		angle = ((float)i / n) * (2 * M_PI);
		x = 100 * cos(angle);
		y = 100 * sin(angle);
		vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
		if (i != 0) {
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
	}




	baloon->InitFromData(vertices, indices);
	return baloon;

}


Baloon::Baloon() {
	baloonM = CreateBaloon("baloon", glm::vec3(1, 0, 0));
	float init_x = ((float)(rand() % 80 + 20) / 100) * 1280;
	float init_y = (float)(rand() % 500) + 800;
	modelMatrix = Transform2D::Translate(init_x, init_y) * Transform2D::Scale(0.3f, 0.35f);
	angular_speed = 1;
	speed = 100;
	angle = 0;
	death_anim = FALSE;
}

Baloon::~Baloon() {}

Mesh* Baloon::getMesh() {
	return baloonM;
}

glm::mat3 Baloon::getModel(float deltaT) {
	if (death_anim) {
		modelMatrix *= Transform2D::Scale(0.8f, 0.8f);
	}
	modelMatrix = Transform2D::Translate(2 * sin(angle += angular_speed * deltaT), - deltaT * speed) * modelMatrix;
	glm::vec3 pos = modelMatrix * glm::vec3(0, 0, 1);
	if (pos.y < -20) {
		death_anim = FALSE;
		float init_x = ((float)(rand() % 80 + 20) / 100) * 1280;
		float init_y = (float)(rand() % 500) + 800;
		modelMatrix = Transform2D::Translate(init_x, init_y) * Transform2D::Scale(0.3f, 0.35f);
		angle = 0;
	}
	return modelMatrix;
}

bool Baloon::collision(glm::mat3 arrow_model) {
	glm::vec3 arrow_tip = arrow_model * glm::vec3(80, 0, 1);
	glm::vec3 center = modelMatrix * glm::vec3(0, 0, 1);
	float a = 0.3f * 100;
	float b = 0.35f * 100;

	float first = arrow_tip.x - center.x;
	first = (first * first) / (a * a);

	float second = arrow_tip.y - center.y;
	second = (second * second) / (b * b);

	if (first + second <= 1) death_anim = TRUE;
	return first + second <= 1;
}