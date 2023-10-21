#ifndef APPLE_H
#define APPLE_H

#include "Snake.h"

class Apple : public GameObject
{
public:

	Apple(glm::vec2 position, glm::vec2 size, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {};

	void ChangePos(const std::vector<Snake*>& snake);

private:

};

#endif // !APPLE_H