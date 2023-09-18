#ifndef GAME_H
#define GAME_H

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
	void Render(float dt);

	// smth


	// pub vars
	bool keys[512];

private:

	int width, height;
	GameState gmState = MENU;
};

#endif // !GAME_H