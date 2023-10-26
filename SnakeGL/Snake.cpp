#include "Snake.h"

void Snake::SetPoint(glm::vec2 position, MoveDirection dir)
{
	point.push(std::make_pair(position, dir));
}

glm::vec2 Snake::GetNosePoint()
{
	glm::vec2 point = position;

	if (mDir == DOWN) point += glm::vec2(size.x / 2.0f, size.y);
	else if (mDir == UP) point.x += size.x / 2.0f;
	else if (mDir == RIGHT) point += glm::vec2(size.x, size.y / 2.0f);
	else if (mDir == RIGHT) point.y += size.y / 2.0f;

	return point;
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
	if (!point.empty() && selfMove) {
		this->mDir = point.front().second;

		Move(dt);

		if ((mDir == DOWN && position.y >= point.front().first.y) ||
			(mDir == UP && position.y <= point.front().first.y) ||
			(mDir == RIGHT && position.x >= point.front().first.x) ||
			(mDir == LEFT && position.x <= point.front().first.x)) {

			point.pop();
			selfMove = false;
		}
	}
	else if (!point.empty() && !selfMove) {
		this->position = point.front().first;
		point.pop();
	}
}
