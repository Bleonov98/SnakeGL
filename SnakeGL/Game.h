#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TextRenderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Snake.h"
#include "Apple.h"

enum GameState {
	MENU,
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
	void Menu();

	void ProcessInput(float dt);
	void Update(float dt);

	void Render();
	void DrawObject(GameObject* obj);
	void DrawStats();

	void Restart();

	// snake
	void AddSnakePart();
	bool TailCollision();

	// pub vars
	bool Keys[1024], KeysProcessed[1024], close = false, restart = false, win = false, endGame = false;

	~Game();

private:

	Shader spriteShader;
	Shader txtShader;

	glm::mat4 projection;

	std::vector<GameObject*> objList;
	std::vector<Snake*> snake;

	int width, height;
	glm::vec2 cursorPos;
	bool firstLoad = true;

	GameState gmState = MENU;
};

#endif // !GAME_H