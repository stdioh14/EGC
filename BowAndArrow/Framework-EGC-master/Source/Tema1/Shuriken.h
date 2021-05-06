#pragma once

#include <string>
#include <Core/Engine.h>
#include "Bow.h"

class Shuriken
{
private:
	Mesh* shurikenM;
	glm::mat3 modelMatrix;
	float angular_speed;
	float speed;
	float death_anim;

public:
	Shuriken();
	~Shuriken();

	Mesh* getMesh();
	glm::mat3 getModel(float dTime);
	bool collision(glm::mat3 bow_model);
	bool collision_a(glm::mat3 arrow_model);
};
