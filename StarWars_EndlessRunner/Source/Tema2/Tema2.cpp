#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

float jump_speed;	//viteza initiala la jump
bool jump;	// True daca e inca in saritura 
float acceleration; //gravitatia
float fuel; //combustibil
float speed; //viteza curenta a player-ului
float time;  //time pt functia de zgomot
Platforms* plat;  //platformele
Player* player;   //playerul
int landed;       //(stiu daca a aterizat sau nu)
bool dead;		  //daca e mort scad vieti si apelez init()
int lives = 3;    //nr vieti
bool applied_pUP; //bool pt a sti daca am aplicat power up-ul
bool max_speed;   //viteza maxima
bool fp;		  //first person
int highscore = 0;
int nr_collect = 0;

Mesh* collect;
float angle = 0;



bool is_power() {
	char power = plat->tiles.at(1)->tiles[player->crt_column];
	return (power == 'o' || power == 'y' ||
		power == 'g' || power == 'o') && player->position.y < 0.1;
}	//return true daca imi ofera power-up


Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	glEnable(GL_TEXTURE_2D); // Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

	renderCameraTarget = false;


	camera = new TemaCam::Camera();
	camera->Set(glm::vec3(0, 2, 3.f), glm::vec3(0, 1.5f, 0), glm::vec3(0, 1, 0));
	//camera->RotateFirstPerson_OX(0.1f);

	glDisable(GL_CULL_FACE);

	projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, 0.01f, 40.0f);

	landed = 0;
	dead = FALSE;
	fp = FALSE;
	applied_pUP = FALSE;
	max_speed = FALSE;
	jump_speed = 0.f;
	time = 5.f;
	jump = FALSE;
	acceleration = 12.0f;
	fuel = 1.f;
	speed = 0.f;
	nr_collect = 0;
	highscore = 0;


	plat = new Platforms();

	plat->plat_mesh[BLUE] = CreateTile("BLUE", glm::vec3(0, 0, 1));
	plat->plat_mesh[YELLOW] = CreateTile("YELLOW", glm::vec3(1, 1, 0));
	plat->plat_mesh[RED] = CreateTile("RED", glm::vec3(1, 0, 0));
	plat->plat_mesh[GREEN] = CreateTile("GREEN", glm::vec3(0, 1, 0));
	plat->plat_mesh[ORANGE] = CreateTile("ORANGE", glm::vec3(1, 0.54f, 0));
	plat->plat_mesh[PURPLE] = CreateTile("PURPLE", glm::vec3(0.69f, 0, 1));

	player = new Player();


	const string textureLoc = "Source/Tema2/Textures/";
 
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "baby_yoda.png").c_str(), GL_REPEAT);
		mapTextures["collect"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "danger.png").c_str(), GL_REPEAT);
		mapTextures["danger"] = texture;
	}
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "wall.png").c_str(), GL_REPEAT);
		mapTextures["wall"] = texture;
	}
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "asteroid.png").c_str(), GL_REPEAT);
		mapTextures["asteroid"] = texture;
	}

	{
		lightPosition_bb8 = glm::vec3(10000, 10000, camera->position.z);
		lightDirection_bb8 = glm::vec3(0, -0.6f, -1);
		lightPosition = glm::vec3(10000, 10000, camera->position.z);
		lightDirection = glm::vec3(-1, -1, 0);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
	}


	{
		Mesh* mesh = new Mesh("collect");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box_yoda.obj");
		meshes[mesh->GetMeshID()] = mesh;
		collect = mesh;
	}

	{
		Mesh* mesh = new Mesh("wall");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box_wall.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "sky.png").c_str(), GL_REPEAT);
		mapTextures["sky"] = texture;
	}

	{
		Mesh* mesh = new Mesh("sky");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box_sky.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "body.png").c_str(), GL_REPEAT);
		mapTextures["body"] = texture;
	}

	{
		Mesh* mesh = new Mesh("body");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "bb8", "body.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "head.png").c_str(), GL_REPEAT);
		mapTextures["head"] = texture;
	}

	{
		Mesh* mesh = new Mesh("head");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "bb8", "head.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}


	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
		player->sphere = mesh;
	}

	// Create a simple cube
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube", vertices, indices);
	}

	// Create fuel
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 0, 1), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(1,  0,  0), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(1,  1,  0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 1)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,  1, 2, 3
		};

		CreateMesh("fuel", vertices, indices);
	}


	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("UiShader");
		shader->AddShader("Source/Tema2/Shaders/UiShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();	//shader pt fuel
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("TexShader");
		shader->AddShader("Source/Tema2/Shaders/VertexShTex.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Tema2/Shaders/FragShTex.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();	//shader pt fuel
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("SkyShader");
		shader->AddShader("Source/Tema2/Shaders/VertexSky.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Tema2/Shaders/FragSky.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();	//shader pt fuel
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("Sphere");
		shader->AddShader("Source/Tema2/Shaders/NoiseShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();  //shader pt cazul in care sunt pe o platforma tip power up
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("Default");
		shader->AddShader("Source/Tema2/Shaders/VertexShaderDefault.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink(); //shader-ul default
		shaders[shader->GetName()] = shader;
	}



}

Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	
	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));


	// ========================================================================


	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

Mesh* Tema2::CreateTile(const char* name, glm::vec3 color) {
	if (!strcmp(name, "ORANGE")) {
		// Load textures
		{

			const string textureLoc = "Source/Tema2/Textures/";

			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "speed2.png").c_str(), GL_REPEAT);
			mapTextures["ORANGE"] = texture;
		}

		{
			Mesh* mesh = new Mesh("ORANGE");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box_orange.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		return meshes["ORANGE"];
	}
	else if (!strcmp(name, "BLUE")) {
		// Load textures
		{

			const string textureLoc = "Source/Tema2/Textures/";

			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "blue_box.png").c_str(), GL_REPEAT);
			mapTextures["BLUE"] = texture;
		}

		{
			Mesh* mesh = new Mesh("BLUE");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box_orange.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		return meshes["BLUE"];
	}
	else if (!strcmp(name, "GREEN")) {
		// Load textures
		{

			const string textureLoc = "Source/Tema2/Textures/";

			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "refuel.png").c_str(), GL_REPEAT);
			mapTextures["GREEN"] = texture;
		}

		{
			Mesh* mesh = new Mesh("GREEN");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box_orange.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		return meshes["GREEN"];
	}
	else if (!strcmp(name, "RED")) {
		// Load textures
		{

			const string textureLoc = "Source/Tema2/Textures/";

			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "blue_box1.png").c_str(), GL_REPEAT);
			mapTextures["RED"] = texture;
		}

		{
			Mesh* mesh = new Mesh("RED");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box_orange.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		return meshes["RED"];
	}
	else if (!strcmp(name, "YELLOW")) {
		// Load textures
		{

			const string textureLoc = "Source/Tema2/Textures/";

			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "energy.png").c_str(), GL_REPEAT);
			mapTextures["YELLOW"] = texture;
		}

		{
			Mesh* mesh = new Mesh("YELLOW");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box_orange.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		return meshes["YELLOW"];
	}
	else {

		{
			std::vector<VertexFormat> vertices
			{
				VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), color),
				VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), color),
				VertexFormat(glm::vec3(-1,  0,  1), glm::vec3(1, 0, 0), color),
				VertexFormat(glm::vec3(1,  0,  1), glm::vec3(0, 1, 0), color),
				VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), color),
				VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), color),
				VertexFormat(glm::vec3(-1,  0, -1), glm::vec3(1, 1, 0), color),
				VertexFormat(glm::vec3(1,  0, -1), glm::vec3(0, 0, 1), color),
			};

			std::vector<unsigned short> indices =
			{
				0, 1, 2,		1, 3, 2,
				2, 3, 7,		2, 7, 6,
				1, 7, 3,		1, 5, 7,
				6, 7, 4,		7, 5, 4,
				0, 4, 1,		1, 4, 5,
				2, 6, 4,		0, 2, 4,
			};
			return CreateMesh(name, vertices, indices);

		}
	}
}	//creaza un tile cu o culoare data



void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::drawTiles() {
	glm::mat4 modelM;
	glm::mat4 modelWall;
	for (Level* lv : plat->tiles) {
		modelM = lv->modelM;

		modelWall = modelM * glm::translate(glm::mat4(1), glm::vec3(-1.5f, 1.2f, 0)) * glm::scale(glm::mat4(1), glm::vec3(1, 2.5f, 2));
		RenderSimpleTex(meshes["wall"], shaders["TexShader"], modelWall, mapTextures["wall"]);

		modelWall = glm::scale(glm::mat4(1), glm::vec3(-1,1,1))  * modelWall;
		RenderSimpleTex(meshes["wall"], shaders["TexShader"], modelWall, mapTextures["wall"]);

		for (int i = 0; i < 5; i++) {

			if (lv->collect[i]) {
				glm::mat4 modelC = glm::translate(glm::mat4(1), glm::vec3(0,1,0)) *
						modelM * glm::rotate(glm::mat4(1), angle, glm::vec3(0,1,0)) * 
						glm::scale(glm::mat4(1), glm::vec3(0.7f, 0.7f, 0.15f));
				RenderSimpleTex(collect, shaders["TexShader"], modelC, mapTextures["collect"]);
			}

			if (lv->tiles[i] == 'n') {
				modelM = glm::translate(modelM, glm::vec3(2.0f, 0, 0));
				continue;
			}
			else if (lv->tiles[i] == 'b' || lv->tiles[i] == 'p') {
				glm::mat4 model = modelM * glm::scale(glm::mat4(1), glm::vec3(2, 1, 2)) * glm::translate(glm::mat4(1), glm::vec3(0, -0.5f, 0));
				RenderSimpleTex(plat->plat_mesh[BLUE], shaders["TexShader"], model, mapTextures["BLUE"]);

				if (lv->danger[i]) {

					glm::mat4 modelD = glm::translate(glm::mat4(1), glm::vec3(0, 1, 0)) * model;

					RenderSimpleTex(meshes["box"], shaders["TexShader"], modelD, mapTextures["danger"]);
				}

			}
			else if (lv->tiles[i] == 'r') {
				glm::mat4 model = modelM * glm::scale(glm::mat4(1), glm::vec3(2, 1, 2)) * glm::translate(glm::mat4(1), glm::vec3(0, -0.5f, 0));
				RenderSimpleTex(plat->plat_mesh[RED], shaders["TexShader"], model, mapTextures["RED"]);
			}
			else if (lv->tiles[i] == 'o') {
				glm::mat4 model = modelM * glm::scale(glm::mat4(1), glm::vec3(2,1,2)) * glm::translate(glm::mat4(1), glm::vec3(0,-0.5f,0));
				RenderSimpleTex(plat->plat_mesh[ORANGE], shaders["TexShader"], model, mapTextures["ORANGE"]);
			}
			else if (lv->tiles[i] == 'y') {
				glm::mat4 model = modelM * glm::scale(glm::mat4(1), glm::vec3(2, 1, 2)) * glm::translate(glm::mat4(1), glm::vec3(0, -0.5f, 0));
				RenderSimpleTex(plat->plat_mesh[YELLOW], shaders["TexShader"], model, mapTextures["YELLOW"]);
			}
			else if (lv->tiles[i] == 'g') {
				glm::mat4 model = modelM * glm::scale(glm::mat4(1), glm::vec3(2, 1, 2)) * glm::translate(glm::mat4(1), glm::vec3(0, -0.5f, 0));
				RenderSimpleTex(plat->plat_mesh[GREEN], shaders["TexShader"], model, mapTextures["GREEN"]);
			}
			modelM = glm::translate(modelM, glm::vec3(2.0f, 0, 0));
		}
	}
	
} //imi deseneaza platformele
  //daca am aterizat pe platforma (landed == 1) si exista o platforma acolo 
  //imi deseneaza o platforma mov


void Tema2::Update(float deltaTimeSeconds)
{



	lightPosition = glm::vec3(10000, 10000, camera->position.z);
	lightPosition_bb8 = player->position + glm::vec3(0, 1.f, -0.3f);


	//RenderSimpleTex(collect, shaders["TexShader"], glm::translate(glm::mat4(1), glm::vec3(0, 1.5f, -2)), mapTextures["collect"], 4);

	angle += deltaTimeSeconds;

	if (dead && lives > 0) {
		if (-player->position.z > (float)highscore) {
			highscore = (int)-player->position.z;
			std::cout << "New highscore: " << highscore << std::endl;
			std::cout << "You got " << nr_collect << " baby yodas!\n";
		}
		lives--;
		std::cout << "You lost a life, remaining: " << lives << "\n";
		dead = FALSE;
		free(player);
		free(plat);
		Init();
		//restart in cazul in care a murit player-ul
	}

	if (max_speed) time -= deltaTimeSeconds;
	if (time < 0) {
		time = 5.f;
		max_speed = FALSE;
		//resetez timpul pentru powerUp ul orange
	}

	fuel -= 0.005f * speed * deltaTimeSeconds;
	//update combustibil

	if (fuel > 0) {
		if (player->position.y < -10.0f) {
			//daca a ajuns sub -10.f pe y atunci clar a murit
			dead = TRUE;
			return;
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.9f, 0.4f, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1, fuel, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.6f, 0));
			RenderSimpleMesh(meshes["fuel"], shaders["UiShader"], modelMatrix);
			//crearea matricii model pentru interfata ce arata restul combustibilului
		}
		{
			drawTiles();
			//desenare tile-uri
		}
		if (plat->tiles[1]->collect[player->crt_column]) {
			plat->tiles[1]->collect[player->crt_column] = false;
			nr_collect++;
		}

		{
			if (!applied_pUP && player->position.y < 0.3f && player->position.y >= 0) {
				

				//aici aplic power up - urile
				applied_pUP = TRUE;
				if (plat->tiles[1]->tiles[player->crt_column] == 'r') {
					dead = TRUE; //daca e red atunci a murit
					return;
				}
				else if (plat->tiles[1]->tiles[player->crt_column] == 'g') {
					fuel += 0.3f;  //daca e green atunci primeste combustibil
					if (fuel > 1) fuel = 1;
				}
				else if (plat->tiles[1]->tiles[player->crt_column] == 'y') {
					fuel -= 0.07f;    //daca e yellow pierde combustibil
					if (fuel < 0) {
						dead = TRUE;
						return;
					}
				}
				else if (plat->tiles[1]->tiles[player->crt_column] == 'o') {
					speed = 15;
					max_speed = TRUE;
					//blochez playerul la viteza maxima (15)
				}
			}
			if (plat->tiles[2]->danger[player->crt_column] && player->position.y < 0.9f && int(-player->position.z) % 2 == 0) {
				speed = 0;
			}
			
			if (player->position.y < 1.1f && player->position.y > 1 &&
				jump_speed < 0 && player->collision(plat) && plat->tiles[1]->danger[player->crt_column]) {
				//if-ul reprezinta defapt coliziunea completa
				//player->collision(plat) verifica daca sub player exista 
				//o platforma sau nu
				jump_speed = 0;
				player->position -= glm::vec3(0, player->position.y - 1, 0);
				jump = FALSE;
				landed = 1;
				//deci dupa if stiu daca a aterizat pe o platforma sau nu
			} else if (player->position.y > 0.9 && player->position.y < 1.1 && 
				!plat->tiles[1]->danger[player->crt_column]) {
				jump = true;
			}

			else if (player->position.y < 0.3f && player->position.y > 0 &&
				jump_speed < 0 && player->collision(plat)) { 
				//if-ul reprezinta defapt coliziunea completa
				//player->collision(plat) verifica daca sub player exista 
				//o platforma sau nu
				
				jump_speed = 0;
				player->position -= glm::vec3(0, player->position.y, 0);
				jump = FALSE;
				landed = 1;
				//deci dupa if stiu daca a aterizat pe o platforma sau nu
			}
			if (jump) {
				jump_speed -= acceleration * deltaTimeSeconds;
				//ecuatia de miscare pe verticala
			}
			else if (!player->collision(plat)) jump = TRUE;
			//daca nu am coliziune si se afla in aer / pamant inseamna ca jump = true
			//deci acest lucru face ca bila sa pice cand merge drept si da de un gol
			glm::mat4 modelMatrix = glm::mat4(1);
			
			//updatez position pt plater (position reprezinta punctul cel mai de jos al playerului
			player->updateForward(speed, fuel, deltaTimeSeconds);
			player->updateUp(jump_speed, deltaTimeSeconds);


			//aflu modelMatrix in functie de positia curenta a bilei
			modelMatrix = glm::translate(modelMatrix, player->position + glm::vec3(0, 0.5f, 0));

			//updatez crt column pentru player sa stiu pe ce coloana ma aflu
			player->crt_column = int(player->position.x + 5) / 2;

			if (((int)-player->position.z) % 2 == 1) {
				plat->generate_line((int)player->position.z, &landed, &applied_pUP);
			}
			//generez ai utilizatorul sa nu vada cum se sterg platformele in spate si apar 
			//liniar in functie de speed datorita z-farului

			if (fp) {
				camera->position = glm::vec3(glm::translate(glm::mat4(1), glm::vec3(0, 0.5f, 0)) * glm::vec4(player->position, 1));
				//daca first person atunci camera urmareste pozitia bilei si nu o mai desenez

				glDepthFunc(GL_LEQUAL);
				glm::mat4 modelSky = glm::translate(glm::mat4(1), camera->position) * glm::rotate(glm::mat4(1), RADIANS(180), glm::vec3(0, 1, 0)) * glm::scale(glm::mat4(1), glm::vec3(3000000, 3000000, 3000000));
				RenderSimpleTex(meshes["sky"], shaders["SkyShader"], modelSky, mapTextures["sky"]);
				glDepthFunc(GL_LESS);
			}
			else {
				camera->position = glm::vec3(glm::translate(modelMatrix, glm::vec3(-player->position.x, -player->position.y, 0)) * glm::vec4(0, 2, 3.0f, 1));
				//repun camera asa cum era la inceput 
				//si daca sunt pe un power up atunci randez playerul cu shaderul pt noise
				//daca nu atunci default

				glDepthFunc(GL_LEQUAL);
				glm::mat4 modelSky = glm::translate(glm::mat4(1), camera->position) * glm::rotate(glm::mat4(1), RADIANS(180), glm::vec3(0,1,0)) * glm::scale(glm::mat4(1), glm::vec3(3000000, 3000000, 3000000)) ;
				RenderSimpleTex(meshes["sky"], shaders["SkyShader"], modelSky, mapTextures["sky"]);
				glDepthFunc(GL_LESS);


				RenderSimpleTex(meshes["head"], shaders["TexShader"], glm::translate(modelMatrix, glm::vec3(0, 0.1f, -0.1f)), mapTextures["head"]);
				modelMatrix *= glm::rotate(glm::mat4(1), player->position.z, glm::vec3(1, 0, 0));
				modelMatrix *= glm::rotate(glm::mat4(1), player->position.x, glm::vec3(0, 1, 0));

				RenderSimpleTex(meshes["body"], shaders["TexShader"], modelMatrix, mapTextures["body"]);

			}
		}

	}
	else dead = TRUE; //inseamna ca nu mai am fuel deci a murit
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderSimpleTex(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);


	int light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

	int light_position_bb8 = glGetUniformLocation(shader->program, "light_position_bb8");
	glUniform3f(light_position_bb8, lightPosition_bb8.x, lightPosition_bb8.y, lightPosition_bb8.z);

	int light_direction_bb8 = glGetUniformLocation(shader->program, "light_direction_bb8");
	glUniform3f(light_direction_bb8, lightDirection_bb8.x, lightDirection_bb8.y, lightDirection_bb8.z);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->position;
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);


	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));



	//TODO : activate texture location 0
	//TODO : Bind the texture1 ID
	//TODO : Send texture uniform value

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
	
	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);
	
	int location1 = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	int location2 = glGetUniformLocation(shader->program, "View");
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	int location3 = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int location4 = glGetUniformLocation(shader->program, "time");
	float engine_time = Engine::GetElapsedTime();
	glUniform1f(location4, engine_time);


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		speed += deltaTime;
		if (speed > 15) speed = 15;
	}
	if (window->KeyHold(GLFW_KEY_S) && !max_speed) {
		speed -= deltaTime;
		if (speed < 0) speed = 0;
	}
	if (window->KeyHold(GLFW_KEY_A)) {
		if (player->position.x > -4.5f) {
			player->updateRight(-deltaTime);
		}
	}
	if (window->KeyHold(GLFW_KEY_D)) {
		if (player->position.x < 4.5f) {
			player->updateRight(deltaTime);
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE && !jump) {
		jump_speed = 7.f;
		jump = TRUE;
	}
	if (key == GLFW_KEY_P) {
		fp ^= TRUE;
	}
	if (key == GLFW_KEY_R) {
		lives = 3;
		std::cout << "Lifes replenished!\n";
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{

}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
		}

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
