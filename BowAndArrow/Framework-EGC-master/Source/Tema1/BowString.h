#pragma once

#include <string>
#include <Core/Engine.h>

class BowString
{
private:
	Mesh* bowSMesh;
	glm::mat3 model1;
	glm::mat3 model2;
	float force;

public:
	BowString();
	~BowString();

	Mesh* getMesh();
	float getForce();
	glm::mat3 getModel1(glm::mat3 bowModel, float deltaT, bool pm1, bool rm1);
	glm::mat3 getModel2(glm::mat3 bow_model, float deltaT, bool pm1, bool rm1);


};
