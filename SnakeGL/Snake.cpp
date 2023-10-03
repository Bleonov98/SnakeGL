#include "Snake.h"

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