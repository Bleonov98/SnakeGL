#ifndef GAME_H
#define GAME_H

#include "GameObject.h"

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
	bool keys[512];

private:

	Shader spriteShader;
	glm::mat4 projection;

	int width, height;
	GameState gmState = MENU;
};

#endif // !GAME_H