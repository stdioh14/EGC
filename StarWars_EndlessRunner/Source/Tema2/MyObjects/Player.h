#include <iostream>
#include <string>
#include <Core/Engine.h>

#include <Tema2/MyObjects/Platforms.h>

class Player
{
public:
	Mesh* sphere;
	glm::vec3 position;
	long long crt_line;
	long long crt_column;

	Player();
	~Player();

	bool collision(Platforms* plat);
	void updateForward(float speed, float fuel, float dtime);
	void updateRight(float dtime);
	void updateUp(float dtime, float speed);

};
