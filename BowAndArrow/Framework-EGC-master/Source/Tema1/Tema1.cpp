#include "Tema1.h"

#include <vector>
#include <iostream>
#include <math.h>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Bow.h"
#include "Arrow.h"
#include "Shuriken.h"
#include "Baloon.h"
#include "Sky.h"
#include "Land.h"
#include "Cloud.h"
#include "PowerBar.h"

using namespace std;

Bow *bow;
Arrow* arrow;
Shuriken* sh[3];
Baloon* bal[3];
Sky* sky;
Land* land;
Cloud *cloud;
PowerBar* pb;
float radians = 0;
bool pressedM1 = FALSE;
bool releasedM1 = FALSE;
int lives = 3;
int score = 0;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;


	bow = new Bow();

	arrow = new Arrow();

	cloud = new Cloud();

	pb = new PowerBar();

	for (int i = 0; i < 3; i++) {
		sh[i] = new Shuriken();
	}
	for (int i = 0; i < 3; i++) {
		bal[i] = new Baloon();
	}

	sky = new Sky();

	land = new Land();

}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::mat3 bow_model = bow->getModel(window);
	RenderMesh2D(bow->getMesh(), shaders["VertexColor"], bow_model);

	glm::mat3 str1_model = bow->getString()->getModel1(bow_model, deltaTimeSeconds, pressedM1, releasedM1);
	RenderMesh2D(bow->getString()->getMesh(), shaders["VertexColor"], str1_model);

	glm::mat3 str2_model = bow->getString()->getModel2(bow_model, deltaTimeSeconds,pressedM1, releasedM1);
	RenderMesh2D(bow->getString()->getMesh(), shaders["VertexColor"], str2_model);

	glm::mat3 arrow_model = arrow->getModel(bow_model,deltaTimeSeconds, bow->getAngle(),releasedM1, pressedM1);
	RenderMesh2D(arrow->getMesh(), shaders["VertexColor"], arrow_model);

	glm::mat3 pb_model = pb->getModel(bow->getString()->getForce(), bow->getPos());
	RenderMesh2D(pb->getMesh(), shaders["VertexColor"], pb_model);



	for (int i = 0; i < 3; i++) {
		if (arrow->in_animation && sh[i]->collision_a(arrow_model)) {
			std::cout << "+100  Shuriken HIT\n\n";
			score += 100;
		}

		glm::mat3 sh_model = sh[i]->getModel(deltaTimeSeconds);
		RenderMesh2D(sh[i]->getMesh(), shaders["VertexColor"], sh_model);

		

		if (sh[i]->collision(bow_model)) {
			lives--;
			std::cout << "you lost a life\n" << "Left:" << lives << std::endl << std::endl;
			if (lives == 0) {
				std::cout << "Your score was: " << score << std::endl;
				window->Close();
			}
		}
	}

	
	for (int i = 0; i < 3; i++) {
		glm::mat3 bal_model = bal[i]->getModel(deltaTimeSeconds);
		RenderMesh2D(bal[i]->getMesh(), shaders["VertexColor"], bal_model);
		if (!bal[i]->death_anim && bal[i]->collision(arrow_model)) {
			std::cout << "+50  Baloon HIT\n\n";
			score += 50;
		}
	}
	
	glm::mat3 cloud_model = cloud->getModel(deltaTimeSeconds);
	RenderMesh2D(cloud->getMesh(), shaders["VertexColor"], cloud_model);

	glm::mat3 land_model = land->getModel();
	RenderMesh2D(land->getMesh(), shaders["VertexColor"], land_model);

	glm::mat3 sky_model = sky->getModel();
	RenderMesh2D(sky->getMesh(), shaders["VertexColor"], sky_model);


	

	/*
	glm::mat3 land_model;


	glm::mat3 cloud_model;
	*/

	releasedM1 = FALSE;


	
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) bow->updateHeight(deltaTime, TRUE);
	if (window->KeyHold(GLFW_KEY_S)) bow->updateHeight(deltaTime, FALSE);
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (button == 1) {
		pressedM1 = TRUE;
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (button == 1) {
		releasedM1 = TRUE;
		pressedM1 = FALSE;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
