#pragma once

#include <string>
#include <Core/Engine.h>

#define MIN_VELO 1
#define MAX_VELO 10

class Arrow
{
private:
	Mesh* arrowMesh;
	glm::vec3 position_tip;
	glm::mat3 modelMatrix;
	float velocity, force, my_angle, time;
	

	

public:
	Arrow();
	~Arrow();
	bool in_animation;
	Mesh* getMesh();
	glm::vec3 getPos();
	glm::mat3 getModel(glm::mat3 bow_model,float deltaT, float angle, bool released, bool pressed);

};
