#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Renderer.h"
#include "AABB.h"

class GameObject
{
public:

	GameObject(glm::vec2 position, glm::vec2 size, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) {
		this->position = position, this->color = color, this->size = size, this->angle = angle;

		hBox.SetBorder(position, position + size);
	};

	// Set
	void SetPos(glm::vec2 position) { this->position = position; }
	void SetSize(glm::vec2 size) { this->size = size; }
	void SetColor(glm::vec3 color) { this->color = color; }
	void SetAngle(float angle) { this->angle = angle; }

	void SetTexture(const char* fileName, bool alpha) { mesh.AddTexture(fileName, alpha); }
	void UpdateAABB() { hBox.SetBorder(position, position + size); }

	// Get
	glm::vec2 GetPos() { return position; }
	glm::vec2 GetSize() { return size; }
	glm::vec3 GetColor() { return color; }
	float GetAngle() { return angle; }

	// main
	void DrawObject() { mesh.Draw(); }

	bool CheckCollision(const GameObject& other) { return hBox.Intersects(other.hBox); }

protected:

	Renderer mesh;
	AABB hBox;

	glm::vec3 color;
	glm::vec2 position, size;
	float angle;

};

#endif // !GAMEOBJECT_H