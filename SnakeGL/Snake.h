#ifndef SNAKE_H
#define SNAKE_H

#include "GameObject.h"

enum MoveDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake : public GameObject
{
public:

	Snake(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->speed = speed;
	};

	// Set
	void SetSpeed(float speed) { this->speed = speed; }
	void SetDirection(MoveDirection mDir) { this->mDir = mDir; }

	// Get
	float GetSpeed() { return speed; }

	// Main
	void Move(float dt);

private:

	float speed;
	int tailSize = 0;

	MoveDirection mDir = DOWN;

};

#endif // !SNAKE_H


