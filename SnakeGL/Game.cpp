#include "Game.h"

GameObject* object;

void Game::Init()
{
    spriteShader.LoadShader("vShader.vx", "fShader.ft");

	// tools
	projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

	// init objects
    object = new GameObject(glm::vec2(200.0f, 200.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(200.0f, 200.0f), 0.0f);
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
	DrawObject(object);
}

void Game::DrawObject(GameObject* obj)
{
    spriteShader.Use();
    spriteShader.SetMatrix4("projection", projection);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(obj->GetPos(), 1.0f));

    model = glm::translate(model, glm::vec3(0.5f * obj->GetSize().x, 0.5f * obj->GetSize().y, 0.0f));
    model = glm::rotate(model, glm::radians(obj->GetAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * obj->GetSize().x, -0.5f * obj->GetSize().y, 0.0f));

    model = glm::scale(model, glm::vec3(obj->GetSize(), 1.0f));

    spriteShader.SetMatrix4("model", model);
    spriteShader.SetVector3f("spriteColor", obj->GetColor());

    obj->DrawObject();
}