#include <string>
#include <Core/Engine.h>
#include <iostream>
#include <vector>

#pragma once
#ifndef LEVEL
#define LEVEL

class Level
{
public:

	char* tiles;
	glm::mat4 modelM;


	Level(char *line, glm::mat4 model);
	~Level();

};

//level va reprezenta un rand din platforme

#endif