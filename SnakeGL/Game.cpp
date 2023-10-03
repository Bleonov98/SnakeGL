#include "Game.h"

GameObject* background;
GameObject* field;

Snake* snake;

void Game::Init()
{
    spriteShader.LoadShader("vShader.vx", "fShader.ft");

	// tools
    projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

	// background/map
    background = new GameObject(glm::vec2(0.0f), glm::vec2(this->width, this->height));
    field = new GameObject(glm::vec2(50.0f), glm::vec2(1080, 720));

    background->SetTexture("cover.jpg", false);
    field->SetTexture("field.png", true);

    // game objects
    snake = new Snake(glm::vec2(field->GetPos().x + fieldOffset.x, field->GetPos().y + fieldOffset.y), glm::vec2(60.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));
    snake->SetTexture("head.png", true);
}

void Game::ProcessInput(float dt)
{
    if (this->Keys[GLFW_KEY_LEFT]) snake->SetDirection(LEFT);
    else if (this->Keys[GLFW_KEY_RIGHT]) snake->SetDirection(RIGHT);
    else if (this->Keys[GLFW_KEY_UP]) snake->SetDirection(UP);
    else if (this->Keys[GLFW_KEY_DOWN]) snake->SetDirection(DOWN);
}

void Game::Update(float dt)
{
    snake->Move(dt);
}

void Game::Render()
{
    // background/map
    DrawObject(background);
    DrawObject(field);

    // game objects
    DrawObject(snake);
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

Game::~Game()
{
    delete background;
    delete field;

    delete snake;
}
