#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameObject.h"
#include "Snake.h"

enum GameState {
	MENU,
	PAUSED,
	ACTIVE
};

class Game
{
public:

	Game(const int width, const int height) {
		this->width = width, this->height = height;
	}
	
	// basics
	void Init();

	void ProcessInput(float dt);
	void Update(float dt);

	void Render();
	void DrawObject(GameObject* obj);

	// smth


	// pub vars
	bool Keys[1024], KeysProcessed[1024];

	~Game();

private:

	Shader spriteShader;
	glm::mat4 projection;

	glm::vec2 fieldOffset = glm::vec2(72.0f, 55.0f);

	int width, height;
	GameState gmState = MENU;
};

#endif // !GAME_H