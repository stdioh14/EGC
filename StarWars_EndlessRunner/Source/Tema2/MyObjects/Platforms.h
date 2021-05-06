#include <iostream>
#include <string>
#include <Core/Engine.h>
#include <vector>
#include "Level.h"

#pragma once
#ifndef PLATFORM
#define PLATFORM

#define BLUE 0
#define YELLOW 1
#define RED 2
#define ORANGE 3
#define GREEN 4
#define PURPLE 5

const char ms1[9][5] = {
	{'n', 'n', 'p', 'n', 'n'},
	{'n', 'n', 'p', 'n', 'n'},
	{'n', 'p', 'p', 'p', 'n'},
	{'n', 'p', 'p', 'p', 'n'},
	{'n', 'p', 'p', 'p', 'n'},
	{'p', 'p', 'p', 'p', 'p'},
	{'o', 'g', 'r', 'b', 'y'},
	{'p', 'p', 'p', 'p', 'p'},
	{'p', 'p', 'p', 'p', 'p'}
};
const char ms2[9][5] = {
	{'n', 'n', 'b', 'n', 'n'},
	{'n', 'n', 'b', 'n', 'n'},
	{'n', 'n', 'b', 'n', 'n'},
	{'n', 'n', 'b', 'n', 'n'},
	{'n', 'n', 'b', 'n', 'n'},
	{'n', 'n', 'b', 'n', 'n'},
	{'n', 'n', 'b', 'n', 'n'},
	{'n', 'n', 'b', 'n', 'n'},
	{'n', 'n', 'b', 'n', 'n'}
};
const char ms3[9][5] = {
	{'b', 'n', 'b', 'n', 'n'},
	{'b', 'n', 'b', 'n', 'n'},
	{'b', 'n', 'b', 'n', 'b'},
	{'n', 'n', 'b', 'n', 'b'},
	{'n', 'n', 'b', 'n', 'n'},
	{'b', 'n', 'b', 'n', 'n'},
	{'b', 'n', 'n', 'n', 'n'},
	{'b', 'n', 'n', 'n', 'n'},
	{'b', 'n', 'n', 'n', 'n'}
};


class Platforms
{
public:

	Mesh* plat_mesh[7];
	std::vector<Level *> tiles;
	int last_generated;

	Platforms();
	~Platforms();

	void generate_line(int place, int* landed, bool* applied);

};


#endif