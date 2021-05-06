#include <string>
#include <Core/Engine.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Platforms.h"






Platforms::Platforms() {
	last_generated = -1;
	glm::mat4 modelM = glm::translate(glm::mat4(1), glm::vec3(-4.0f, 0, 0));
	for (int i = 8; i >= 0; i--) {
		char* tile = (char*)malloc(5 * sizeof(char));
		for (int j = 0; j < 5; j++) {
			tile[j] = ms1[i][j];
		}
		Level* lv = new Level(tile, modelM);
		tiles.push_back(lv);
		modelM = glm::translate(modelM, glm::vec3(0, 0, -2.0f));
	}
	for (int i = 8; i >= 0; i--) {
		char* tile = (char*)malloc(5 * sizeof(char));
		for (int j = 0; j < 5; j++) {
			tile[j] = ms2[i][j];
		}
		Level* lv = new Level(tile, modelM);
		tiles.push_back(lv);
		modelM = glm::translate(modelM, glm::vec3(0, 0, -2.0f));
	}
	for (int i = 8; i >= 0; i--) {
		char* tile = (char*)malloc(5 * sizeof(char));
		for (int j = 0; j < 5; j++) {
			tile[j] = ms3[i][j];
		}
		Level* lv = new Level(tile, modelM);
		tiles.push_back(lv);
		modelM = glm::translate(modelM, glm::vec3(0, 0, -2.0f));
	}
}  //pregatesc startul (care arata mereu la fel)
   //se gaseste in cele 3 matrici din platforms.h

char get_type(int random) {
	if (random > 50) return 'n';
	if (random < 30) return 'b';
	else if (random < 32) return 'r';
	else if (random < 35) return 'g';
	else if (random < 45) return 'y';
	else return 'o';
}  //in functie de intul random generez platforma

void Platforms::generate_line(int place, int *landed, bool *applied) {
	srand(time(NULL));
	if (place == last_generated) return;
	delete tiles[0];
	tiles.erase(tiles.begin());
	char* line = (char*)malloc(5 * sizeof(char));
	{
		int random = rand() % 101;
		line[0] = get_type(random);
		random = rand() % 101;
		line[1] = get_type(random);
		random = rand() % 101;
		line[2] = get_type(random);
		random = rand() % 101;
		line[3] = get_type(random);
		random = rand() % 101;
		line[4] = get_type(random);
	}
	glm::mat4 modelM = glm::translate(tiles.back()->modelM, glm::vec3(0,0,-2.f));
	last_generated = place;
	Level* newL = new Level(line, modelM);
	tiles.push_back(newL);
	*landed = 0;
	*applied = FALSE;

	//ca sa generez ceva nou voi sterge prima platforma si voi genera una nou
	//pe care o voi pune la final
}



