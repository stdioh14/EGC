#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "TemaCam.h"
#include <Tema2/MyObjects/Platforms.h>
#include <Tema2/MyObjects/Level.h>
#include <Tema2/MyObjects/Player.h>


class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	Mesh* CreateTile(const char* name, glm::vec3 color);
	void drawTiles();


private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
	void RenderTex(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1);
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	std::unordered_map<std::string, Texture2D*> mapTextures;

protected:
	TemaCam::Camera* camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
};
