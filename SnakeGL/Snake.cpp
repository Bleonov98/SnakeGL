#include "Snake.h"

void Snake::SetPoint(glm::vec2 position, MoveDirection dir)
{
	point.push(std::make_pair(position, dir));
}

void Snake::Move(float dt)
{
	if (mDir == DOWN) {
		position.y += speed * dt;
		angle = 0.0f;
	}
	else if (mDir == UP) { 
		position.y -= speed * dt;
		angle = 180.0f;
	}
	else if (mDir == RIGHT) { 
		position.x += speed * dt;
		angle = 270.0f;
	}
	else if (mDir == LEFT) { 
		position.x -= speed * dt;
		angle = 90.0f;
	}
}

void Snake::TailMove(float dt)
{
	if (!point.empty()) {
		this->mDir = point.front().second;

		if ((mDir == DOWN && position.y >= point.front().first.y) ||
			(mDir == UP && position.y <= point.front().first.y) || 
			(mDir == RIGHT && position.x >= point.front().first.x) ||
			(mDir == LEFT && position.x <= point.front().first.x)) point.pop();

		Move(dt);
	}
}
