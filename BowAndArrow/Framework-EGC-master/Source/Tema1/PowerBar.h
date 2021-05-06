#include <string>
#include <Core/Engine.h>

#ifndef POWERBAR_HEADER
#define POWERBAR_HEADER




class PowerBar
{
public:
	Mesh* pbM;
	glm::mat3 modelMatrix;

	PowerBar();
	~PowerBar();

	Mesh* getMesh();
	glm::mat3 getModel(float force, glm::vec3 position);
};

#endif