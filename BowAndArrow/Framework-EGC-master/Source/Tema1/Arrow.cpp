#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Arrow.h"
#include <iostream>

#define MAX_FORCE 0.3f
#define G_FORCE 3

float last_angle = 0;

Mesh* CreateArrow(std::string name, glm::vec3 color)
{

	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};

	Mesh* arrow = new Mesh(name);

	vertices.push_back(VertexFormat(glm::vec3(80, 0, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(75, 4, 0), color));   //varfu
	vertices.push_back(VertexFormat(glm::vec3(75, -4, 0), color));

	vertices.push_back(VertexFormat(glm::vec3(75, 2, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(75, -2, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(4, 2, 0), color));	//body
	vertices.push_back(VertexFormat(glm::vec3(4, -2, 0), color));

	vertices.push_back(VertexFormat(glm::vec3(0, 10, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(0, -10, 0), color));	//pana
	vertices.push_back(VertexFormat(glm::vec3(4, 0, 0), color));


	indices.push_back(0);
	indices.push_back(1);	//varf
	indices.push_back(2);

	//body
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(5);

	indices.push_back(6);
	indices.push_back(5);
	indices.push_back(4);

	//pana

	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(9);

	indices.push_back(8);
	indices.push_back(9);
	indices.push_back(6);

	arrow->InitFromData(vertices, indices);
	return arrow;
	
}


Arrow::Arrow() {
	arrowMesh = CreateArrow("arrow", glm::vec3(0, 0, 0));
	position_tip = glm::vec3(80, 0, 1);
	modelMatrix = glm::mat3(1);
	velocity = MIN_VELO;
	in_animation = FALSE;
	force = 0;
	my_angle = 0;
}

Arrow::~Arrow() {}

Mesh* Arrow::getMesh() {
	return arrowMesh;
}


glm::vec3 Arrow::getPos() {
	return modelMatrix * glm::vec3(80,0,1);
}

glm::mat3 Arrow::getModel(glm::mat3 bow_model, float deltaT, float angle, bool released, bool pressed) {
	
	position_tip = glm::vec3(80, 0, 1);

	if (pressed && !in_animation) {
		force += deltaT / 4;
		if (force > MAX_FORCE) force = MAX_FORCE;
		velocity = (force/MAX_FORCE) * MAX_VELO;
		if (velocity < MIN_VELO) velocity = MIN_VELO;
		my_angle = angle;
		modelMatrix = bow_model * Transform2D::Translate(70 - 120 * force, 0);
		time = 0;
		last_angle = my_angle;
		return modelMatrix;
	}
	else if (released || in_animation) {
		in_animation = TRUE;
		time += deltaT;
		float x_velo = velocity * cos(my_angle);
		float y_velo = velocity * sin(my_angle) - G_FORCE * time * time / 2;

		float angle2 = glm::atan(y_velo / x_velo) - last_angle;
		last_angle += angle2;

		modelMatrix = Transform2D::Translate(x_velo, y_velo) * modelMatrix * Transform2D::Rotate(angle2);
 
		glm::vec3 pos = modelMatrix * position_tip;

		if (pos.x > 1350) in_animation = FALSE;
		if (pos.y > 800) in_animation = FALSE;
		if (pos.x < -50) in_animation = FALSE;
		if (pos.y < -50) in_animation = FALSE;
		return modelMatrix;
	}
	else {
		last_angle = 0;
		force = 0;
		time = 0;
		velocity = MIN_VELO;
		modelMatrix = bow_model * Transform2D::Translate(70, 0);
		return modelMatrix;
	}
}
