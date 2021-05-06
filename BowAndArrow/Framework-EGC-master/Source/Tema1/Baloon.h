#pragma once

#include <string>
#include <Core/Engine.h>
#include "Baloon.h"

class Baloon
{
private:
	Mesh* baloonM;
	glm::mat3 modelMatrix;
	float angular_speed;
	float angle;
	float speed;
public:
	Baloon();
	~Baloon();

	bool death_anim;

	Mesh* getMesh();
	glm::mat3 getModel(float dTime);
	bool collision(glm::mat3 arrow_model);
};
