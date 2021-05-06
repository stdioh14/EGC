#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Bow.h"

Mesh* CreateBow(std::string name, glm::vec3 color)
{

	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};


	Mesh* bow = new Mesh(name);
	int n = 1000;

	int r = 100;
	float width = 4;
	int nr_indices = 0;
	for (int i = -n / 2; i < n / 2; i++) {
		float angle1 = (AI_MATH_PI * i) / (2 * n);
		float x1 = r * cos(angle1);
		float y1 = r * sin(angle1);

		float angle2 = (AI_MATH_PI * (i + 1)) / (2 * n);
		float x2 = r * cos(angle2);
		float y2 = r * sin(angle2);

		float angle_top1 = (angle1 + angle2) / 2;
		float x_top1 = (r - width) * cos(angle_top1);
		float y_top1 = (r - width) * sin(angle_top1);


		float angle_top2 = (angle2 + ((AI_MATH_PI * (i + 2)) / (2 * n))) / 2;
		float x_top2 = (r - width) * cos(angle_top2);
		float y_top2 = (r - width) * sin(angle_top2);


		vertices.push_back(VertexFormat(glm::vec3(x1, y1, 0), color));
		vertices.push_back(VertexFormat(glm::vec3(x2, y2, 0), color));
		vertices.push_back(VertexFormat(glm::vec3(x_top1, y_top1, 0), color));

		indices.push_back(nr_indices + (i + n / 2));
		indices.push_back(nr_indices + 1 + (i + n / 2));
		indices.push_back(nr_indices + 2 + (i + n / 2));

		if (i < (n / 2) - 1) {
			vertices.push_back(VertexFormat(glm::vec3(x_top2, y_top2, 0), color));
			indices.push_back(nr_indices + 1 + (i + n / 2));

			indices.push_back(nr_indices + 3 + (i + n / 2));
			indices.push_back(nr_indices + 2 + (i + n / 2));
			nr_indices++;
		}
		nr_indices += 2;

	}
	bow->InitFromData(vertices, indices);
	return bow;
}


Bow::Bow() {
	bowMesh = CreateBow("bow", glm::vec3(0.54f, 0.27f, 0.07f));
	position = glm::vec3(0, 0, 0);
	modelMatrix = glm::mat3(1);
	str = new BowString();
}

Bow::~Bow(){}

Mesh* Bow::getMesh() {
	return bowMesh;
}

BowString* Bow::getString() {
	return str;
}

glm::vec3 Bow::getPos() {
	return position;
}

glm::mat3 Bow::getModel(WindowObject *window){
	double xpos, ypos;
	glfwGetCursorPos(window->window, &xpos, &ypos);
	ypos = 720 - ypos;
	angle = atan((ypos - position.y) / xpos);
	modelMatrix = Transform2D::Translate(40, position.y) * Transform2D::Rotate(angle);
	return modelMatrix;
}

void Bow::updateHeight(float dtime, bool up) {
	if (up) {
		position += glm::vec3(0,300 * dtime, 0);
	}
	else {
		position -= glm::vec3(0, 300 * dtime, 0);
	}
}

float Bow::getAngle() {
	return angle;
}