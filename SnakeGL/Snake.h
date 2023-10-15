#ifndef SNAKE_H
#define SNAKE_H

#include "GameObject.h"

#include <list>
#include <queue>

enum MoveDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef std::pair<glm::vec2, MoveDirection> pair_p;

class Snake : public GameObject
{
public:

	Snake(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->speed = speed;
	};

	// Set
	void SetSpeed(float speed) { this->speed = speed; }
	void SetDirection(MoveDirection mDir) { this->mDir = mDir; }
	void SetPoint(glm::vec2 position, MoveDirection dir);

	// Get
	float GetSpeed() { return speed; }
	MoveDirection GetDirection() { return mDir; }

	void Move(float dt);
	void TailMove(float dt);

protected:

	float speed;

	std::queue<pair_p, std::list<pair_p>> point;

	MoveDirection mDir = DOWN;
};

#endif // !SNAKE_H


