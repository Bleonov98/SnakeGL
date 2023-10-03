#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Renderer.h"

class GameObject
{
public:

	GameObject(glm::vec2 position, glm::vec2 size, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) {
		this->position = position, this->color = color, this->size = size, this->angle = angle;
	};

	// Set
	void SetPos(glm::vec2 position) { this->position = position; }
	void SetSize(glm::vec2 size) { this->size = size; }
	void SetColor(glm::vec3 color) { this->color = color; }
	void SetAngle(float angle) { this->angle = angle; }
	void SetTexture(const char* fileName, bool alpha) { mesh.AddTexture(fileName, alpha); }

	// Get
	glm::vec2 GetPos() { return position; }
	glm::vec2 GetSize() { return size; }
	glm::vec3 GetColor() { return color; }
	float GetAngle() { return angle; }

	// main
	void DrawObject() { mesh.Draw(); }

protected:

	Renderer mesh;

	glm::vec3 color;
	glm::vec2 position, size;
	float angle;

};

#endif // !GAMEOBJECT_H