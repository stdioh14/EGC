#include <string>
#include <Core/Engine.h>
#include <iostream>
#include <vector>

#include "Player.h"

Player::Player() {
	position = glm::vec3(0, 0, -2.0f);
}

bool Player::collision(Platforms* plat) {  
	return (plat->tiles[1]->tiles[crt_column] != 'n'); 
} //e deasupra unei platforme cand nu e de tip 'n'

void Player::updateForward(float speed, float fuel, float dtime) {
	if (fuel > 0) {
		position += glm::vec3(0, 0, -speed * dtime);
	}  //deplases position cu -speed*time pe axa oz
}

void Player::updateRight(float dtime) {
	position += glm::vec3(dtime * 5, 0, 0);
}  //updatez stanga dreapta

void Player::updateUp(float dtime, float speed) {
	position += glm::vec3(0, dtime * speed, 0);
}   //updatez pe directia Oy cand sare