#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Cloud.h"



Mesh* createCloud() {
	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};

	glm::vec3 color = glm::vec3(0.95f, 0.94f, 0.90f);

	Mesh* cloud = new Mesh("");

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

	vertices.push_back(VertexFormat(glm::vec3(130, 60, 0), color));
	for (int i = n + 2; i <= 2 * n + 4; i++) {
		angle = ((float)(i - n - 2) / n) * (2 * M_PI);
		x = 120 * cos(angle) + 130;
		y = 120 * sin(angle) + 60;
		vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
		if (i != n + 2) {
			indices.push_back(n + 2);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
	}
	vertices.push_back(VertexFormat(glm::vec3(250, 0, 0), color));
	for (int i = 2 * n + 6; i <= 3 * n + 8; i++) {
		angle = ((float)(i - 2 * n - 6) / n) * (2 * M_PI);
		x = 100 * cos(angle) + 250;
		y = 100 * sin(angle);
		vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
		if (i != n + 2) {
			indices.push_back(2 * n + 2);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
	}

	cloud->InitFromData(vertices, indices);
	return cloud;
}


Cloud::Cloud() {
	cloudM = createCloud();
}

Cloud::~Cloud() {}

Mesh* Cloud::getMesh() {
	return cloudM;
}

glm::mat3 Cloud::getModel(float deltaT) {
	distance += 10 * deltaT;
	if (distance > 1400) {
		distance = 0;
	}
	modelMatrix = Transform2D::Translate(1350 - distance, 600) * Transform2D::Scale(0.6f,0.6f);
	return modelMatrix;
}