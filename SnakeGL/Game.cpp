#include "Game.h"

std::unique_ptr<GameObject> background;
std::unique_ptr<GameObject> field;

void Game::Init()
{
    spriteShader.LoadShader("vShader.vx", "fShader.ft");

	// tools
	projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

	// background/map
    background = std::make_unique<GameObject>(glm::vec2(0.0f), glm::vec2(this->width, this->height));
    background->SetTexture("cover.jpg", false);

    field = std::make_unique<GameObject>(glm::vec2(50.0f), glm::vec2(1080.0f, 720.0f));
    field->SetTexture("field.png", true);

    // game objects
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
    // background/map
	DrawObject(background);
    DrawObject(field);

    // game objects
}

void Game::DrawObject(std::unique_ptr<GameObject>& obj)
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