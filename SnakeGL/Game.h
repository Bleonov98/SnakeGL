#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameObject.h"
#include "Snake.h"
#include "Apple.h"
#include <thread>

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

	// snake
	void AddSnakePart();


	// pub vars
	bool Keys[1024], KeysProcessed[1024];

	~Game();

private:

	Shader spriteShader;
	glm::mat4 projection;

	std::vector<GameObject*> objList;
	std::vector<Snake*> snake;

	int width, height;
	GameState gmState = MENU;
};

#endif // !GAME_H