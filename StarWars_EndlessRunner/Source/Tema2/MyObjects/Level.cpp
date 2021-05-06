#include <string>
#include <Core/Engine.h>
#include <iostream>
#include <vector>

#include "Level.h"





Level::Level(char *line, bool *col, bool *dan,  glm::mat4 model) {
	tiles = line;
	modelM = model;
	collect = col;
	danger = dan;
}

Level::~Level() {
	free(tiles);
}