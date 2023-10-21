#include "Game.h"

GameObject* background;
GameObject* field;

Snake* head;
Apple* apple;

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
    snake.reserve(40);
    
    head = new Snake(glm::vec2(150.0f), glm::vec2(60.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));
    head->SetTexture("head.png", true);
    snake.push_back(head);
    objList.push_back(head);

    apple = new Apple(glm::vec2(150.0f), glm::vec2(30.0f));
    apple->SetTexture("apple.png", true);
    objList.push_back(apple);
}

void Game::ProcessInput(float dt)
{
    if (this->Keys[GLFW_KEY_LEFT] && head->GetDirection() != RIGHT) head->SetDirection(LEFT);
    else if (this->Keys[GLFW_KEY_RIGHT] && head->GetDirection() != LEFT) head->SetDirection(RIGHT);
    else if (this->Keys[GLFW_KEY_UP] && head->GetDirection() != DOWN) head->SetDirection(UP);
    else if (this->Keys[GLFW_KEY_DOWN] && head->GetDirection() != UP) head->SetDirection(DOWN);
}

void Game::Update(float dt)
{
    // movement
    for (size_t i = 1; i < snake.size(); ++i)
    {
        snake[i]->SetPoint(snake[i - 1]->GetPos(), snake[i - 1]->GetDirection());
    }
    
    for (size_t i = 0; i < snake.size(); ++i)
    {
        if (i == 0) snake[i]->Move(dt);
        else snake[i]->TailMove(dt);
    }
    
    // update borders after position changes
    for (auto i : objList)
    {
        i->UpdateAABB();
    }

    if (head->CheckCollision(*apple)) {
        head->AddScore();
        AddSnakePart();
        apple->ChangePos(snake);
    } // snake and apple collision
}

void Game::Render()
{
    // background/map
    DrawObject(background);
    DrawObject(field);

    // game objects
    for (auto i : snake)
    {
        DrawObject(i);
    }

    DrawObject(apple);
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

void Game::AddSnakePart()
{
    Snake* body = nullptr;

    if (snake.back()->GetDirection() == DOWN) body = new Snake(glm::vec2(snake.back()->GetPos().x, snake.back()->GetPos().y - 55.0f), glm::vec2(60.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));
    else if (snake.back()->GetDirection() == UP) body = new Snake(glm::vec2(snake.back()->GetPos().x, snake.back()->GetPos().y + 55.0f), glm::vec2(60.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));
    else if (snake.back()->GetDirection() == LEFT) body = new Snake(glm::vec2(snake.back()->GetPos().x + 55.0f, snake.back()->GetPos().y), glm::vec2(60.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));
    else if (snake.back()->GetDirection() == RIGHT) body = new Snake(glm::vec2(snake.back()->GetPos().x - 55.0f, snake.back()->GetPos().y), glm::vec2(60.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));

    if (body != nullptr) {
        body->SetTexture("body.png", true);
        snake.push_back(body);
    }
}

Game::~Game()
{
    delete background;
    delete field;

    // snake
    for (size_t i = 1; i < snake.size(); ++i)
    {
        delete snake[i];
    }

    snake.clear();
    // -----



}
