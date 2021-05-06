#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Shuriken.h"

Mesh* CreateShuriken(std::string name, glm::vec3 color)
{

	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};


	Mesh* shuriken = new Mesh(name);

	vertices.push_back(VertexFormat(glm::vec3(-100, -100, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(100, -100, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(-100, 100, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(100, 100, 0), color));

	
	vertices.push_back(VertexFormat(glm::vec3(-400, 0, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(0, -400, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(400, 0, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(0, 400, 0), color));
	
	//patrat din shuriken
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3); 

	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(0);

	//varfurile
	
	indices.push_back(4);
	indices.push_back(0);
	indices.push_back(2);

	
	
	indices.push_back(5);
	indices.push_back(0);
	indices.push_back(1);

	
	indices.push_back(6);
	indices.push_back(1);
	indices.push_back(3);

	
	indices.push_back(7);
	indices.push_back(2);
	indices.push_back(3);

	shuriken->InitFromData(vertices, indices);
	return shuriken;
	
}


Shuriken::Shuriken() {
	shurikenM = CreateShuriken("shuriken", glm::vec3(0, 0, 0));
	float init_y = ((float)(rand() % 100) / 100) * 720;
	float init_x = (float)(rand() % 500) + 1300;
	modelMatrix = Transform2D::Translate(init_x, init_y) *Transform2D::Scale(0.1f, 0.1f);
	angular_speed = 5;
	speed = 300;
	death_anim = FALSE;
}

Shuriken::~Shuriken() {}

Mesh* Shuriken::getMesh() {
	return shurikenM;
}

glm::mat3 Shuriken::getModel(float deltaT) {
	modelMatrix = Transform2D::Translate(-deltaT * speed, 0) * modelMatrix * Transform2D::Rotate(angular_speed * deltaT);
	glm::vec3 pos = modelMatrix * glm::vec3(400, 0, 1);
	if(pos.x < -50) {
		float init_y = ((float)(rand() % 100) / 100) * 720;
		float init_x = (float)(rand() % 500) + 1300;
		modelMatrix = Transform2D::Translate(init_x, init_y) * Transform2D::Scale(0.1f, 0.1f);
	}
	return modelMatrix;
}

bool Shuriken::collision(glm::mat3 bow_model) {
	float x = 100 * sin(AI_MATH_PI / 4);
	glm::vec3 A = bow_model * glm::vec3(x, x, 1);
	glm::vec3 B = bow_model * glm::vec3(100, 0, 1);
	glm::vec3 C = bow_model * glm::vec3(x, -x, 1);

	//printf("Sus: %f %f   Mijloc: %f %f  Jos: %f %f\n", A.x, A.y, B.x, B.y, C.x, C.y);

	std::vector<glm::vec3> points
	{
		modelMatrix * glm::vec3(-400, 0, 1),
		modelMatrix * glm::vec3(400, 0, 1),
		modelMatrix * glm::vec3(0, -400, 1),
		modelMatrix * glm::vec3(0, 400, 1)
	};

	for (glm::vec3 p : points) {
		float Fac1 = (C.y - A.y) * p.x + (A.x - C.x) * p.y + C.x * A.y - A.x * C.y;
		float Fac2 = (C.y - A.y) * B.x + (A.x - C.x) * B.y + C.x * A.y - A.x * C.y;

		float Fbc1 = (B.y - C.y) * p.x + (C.x - B.x) * p.y + B.x * C.y - C.x * B.y;
		float Fbc2 = (B.y - C.y) * A.x + (C.x - B.x) * A.y + B.x * C.y - C.x * B.y;

		float alfa = Fbc1 / Fbc2;
		float beta = Fac1 / Fac2;
		float gama = 1 - alfa - beta;

		if (0 < alfa && alfa < 1 && 0 < beta && beta < 1 && 0 < gama && gama < 1) {
			float init_y = ((float)(rand() % 100) / 100) * 720;
			float init_x = (float)(rand() % 500) + 1300;
			modelMatrix = Transform2D::Translate(init_x, init_y) * Transform2D::Scale(0.1f, 0.1f);
			return TRUE;
		}
	}

	return FALSE;
}

bool Shuriken::collision_a(glm::mat3 arrow_model) {
	glm::vec3 p = arrow_model * glm::vec3(80, 0, 1);

	//printf("Sus: %f %f   Mijloc: %f %f  Jos: %f %f\n", A.x, A.y, B.x, B.y, C.x, C.y);

	glm::vec3 center = modelMatrix * glm::vec3(0, 0, 1);

	float x = (p.x - center.x) * (p.x - center.x) / (35 * 35);
	float y = (p.y - center.y) * (p.y - center.y) / (35 * 35);

	if (x + y <= 1) {
		float init_y = ((float)(rand() % 100) / 100) * 720;
		float init_x = (float)(rand() % 500) + 1300;
		modelMatrix = Transform2D::Translate(init_x, init_y) * Transform2D::Scale(0.1f, 0.1f);
		return TRUE;
	}
	

	return FALSE;
}