#include <string>
#include <Core/Engine.h>



class Cloud
{
private:
	Mesh* cloudM;
	glm::mat3 modelMatrix;
	float distance;
public:
	Cloud();
	~Cloud();

	Mesh* getMesh();
	glm::mat3 getModel(float deltaT);
};
