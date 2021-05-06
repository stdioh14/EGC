#pragma once

#include <string>
#include <Core/Engine.h>
#include "BowString.h"

class Bow
{
private:
	Mesh* bowMesh;
	glm::vec3 position;
	glm::mat3 modelMatrix;
	BowString* str;
	float angle;

public:
	Bow();
	~Bow();

	Mesh* getMesh();
	glm::vec3 getPos();
	glm::mat3 getModel(WindowObject *window);
	BowString* getString();
	float getAngle();
	void updateHeight(float dtime, bool up);
	
};
