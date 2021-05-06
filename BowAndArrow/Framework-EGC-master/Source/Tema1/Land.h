#include <string>
#include <Core/Engine.h>



class Land
{
private:
	Mesh* landM;
	glm::mat3 modelMatrix;
public:
	Land();
	~Land();

	Mesh* getMesh();
	glm::mat3 getModel();
};
