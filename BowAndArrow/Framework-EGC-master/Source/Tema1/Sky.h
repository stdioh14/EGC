#include <string>
#include <Core/Engine.h>



class Sky
{
private:
	Mesh* skyM;
	glm::mat3 modelMatrix;
public:
	Sky();
	~Sky();

	Mesh* getMesh();
	glm::mat3 getModel();
};
