#include <string>
#include <Core/Engine.h>
#include <iostream>
#include <vector>

#include "Level.h"





Level::Level(char *line, glm::mat4 model) {
	tiles = line;
	modelM = model;
}

Level::~Level() {
	free(tiles);
}