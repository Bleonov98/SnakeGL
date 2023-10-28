#include "Game.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

TextRenderer* txt;

ISoundEngine* snd = irrklang::createIrrKlangDevice();

GameObject* background;
GameObject* field;

Snake* head;
Apple* apple;

void Game::Init()
{
    // resources
    if (!restart) {
        spriteShader.LoadShader("vShader.vx", "fShader.ft");

        ResourceManager::LoadTexture("cover.jpg", false, "cover");
        ResourceManager::LoadTexture("field.png", true, "field");
        ResourceManager::LoadTexture("head.png", true, "head");
        ResourceManager::LoadTexture("body.png", true, "body");
        ResourceManager::LoadTexture("apple.png", true, "apple");
        
        ISoundSource* music = snd->addSoundSourceFromFile("../sounds/snake.mp3");
        music->setDefaultVolume(0.2f);
        snd->play2D(music, true);
    }

	// tools
    projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    txt = new TextRenderer(this->width, this->height);
    txt->Load("../fonts/Garamond.ttf", 28);
    cursorPos = glm::vec2(width / 2.0f - 50.0f, height / 2.0f);

	// background/map
    background = new GameObject(glm::vec2(0.0f, 45.0f), glm::vec2(this->width, this->height));
    field = new GameObject(glm::vec2(50.0f), glm::vec2(1080, 720));

    background->SetTexture(ResourceManager::GetTexture("cover"));
    field->SetTexture(ResourceManager::GetTexture("field"));

    // game objects
    snake.reserve(80);
    
    head = new Snake(glm::vec2(150.0f), glm::vec2(30.0f), 250.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));
    head->SetTexture(ResourceManager::GetTexture("head"));
    snake.push_back(head);
    objList.push_back(head);

    apple = new Apple(glm::vec2(150.0f), glm::vec2(30.0f));
    apple->SetTexture(ResourceManager::GetTexture("apple"));
    objList.push_back(apple);
}

void Game::Menu()
{
    txt->RenderText("MENU", glm::vec2(this->width / 2.0f - 65.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));

    if (endGame) {
        txt->RenderText("YOU LOSE", glm::vec2(this->width / 2.0f - 125.0f, this->height / 2.0f - 216.0f), 2.0f, glm::vec3(0.75f, 0.0f, 0.0f));

        txt->RenderText("Restart", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
        txt->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));
    }
    else if (firstLoad) {
        txt->RenderText("Start", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
        txt->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));
    }
    else {
        txt->RenderText("Resume", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
        txt->RenderText("Restart", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));
        txt->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 80.0f), 1.0f, glm::vec3(1.0f));
    }

    txt->RenderText("->", glm::vec2(cursorPos), 1.0f, glm::vec3(1.0f));
}

void Game::ProcessInput(float dt)
{
    if (gmState == ACTIVE) {
        if (this->Keys[GLFW_KEY_LEFT] && head->GetDirection() != RIGHT) head->SetDirection(LEFT);
        else if (this->Keys[GLFW_KEY_RIGHT] && head->GetDirection() != LEFT) head->SetDirection(RIGHT);
        else if (this->Keys[GLFW_KEY_UP] && head->GetDirection() != DOWN) head->SetDirection(UP);
        else if (this->Keys[GLFW_KEY_DOWN] && head->GetDirection() != UP) head->SetDirection(DOWN);
        else if (this->Keys[GLFW_KEY_SPACE]) gmState = PAUSED;
    }
    else {
        if (this->Keys[GLFW_KEY_UP] && !this->KeysProcessed[GLFW_KEY_UP] && cursorPos.y > this->height / 2.0f) {
            cursorPos.y -= 40.0f;
            this->KeysProcessed[GLFW_KEY_UP] = true;
        }
        else if (this->Keys[GLFW_KEY_DOWN] && !this->KeysProcessed[GLFW_KEY_DOWN] && cursorPos.y < this->height / 2.0f + 80.0f) {
            cursorPos.y += 40.0f;
            this->KeysProcessed[GLFW_KEY_DOWN] = true;
            if ((firstLoad || endGame) && cursorPos.y == this->height / 2.0f + 80.0f) cursorPos.y -= 40.0f;
        }
        else if (this->Keys[GLFW_KEY_ENTER]) {
            if (endGame) {
                if (cursorPos.y == this->height / 2.0f) Restart();
                else if (cursorPos.y == this->height / 2.0f + 40.0f) close = true;
            }
            else if (firstLoad) {
                if (cursorPos.y == this->height / 2.0f) gmState = ACTIVE;
                else if (cursorPos.y == this->height / 2.0f + 40.0f) close = true;
            }
            else {
                if (cursorPos.y == this->height / 2.0f) gmState = ACTIVE;
                else if (cursorPos.y == this->height / 2.0f + 40.0f) Restart();
                else if (cursorPos.y == this->height / 2.0f + 80.0f) close = true;
            }
        }
    }
}

void Game::Update(float dt)
{
    if (gmState == ACTIVE) {
        if (firstLoad) firstLoad = false;

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
            apple->ChangePos(snake);
            head->AddScore();
            AddSnakePart();
            snd->play2D("../sounds/apple.wav");
        } // snake and apple collision
        if (head->FieldCollision()) {
            endGame = true;
            gmState = MENU;
            snd->play2D("../sounds/crash.mp3");
        }
        if (TailCollision()) {
            endGame = true;
            gmState = MENU;
            snd->play2D("../sounds/crash.mp3");
        }
    }
}

void Game::Render()
{
    // background/map
    DrawObject(background);
    DrawObject(field);

    DrawStats();

    if (gmState == ACTIVE) {
        // game objects
        for (auto i : snake)
        {
            DrawObject(i);
        }

        DrawObject(apple);
    }
    else if (gmState == PAUSED) {
        // game objects
        for (auto i : snake)
        {
            DrawObject(i);
        }

        DrawObject(apple);

        Menu();
    }
    else {
        Menu();
    }

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
    
    if (gmState != ACTIVE) spriteShader.SetBool("menu", true);
    else spriteShader.SetBool("menu", false);

    obj->DrawObject();
}

void Game::DrawStats()
{
    std::string score = "Score: ";

    score += std::to_string(head->GetScore());

    glm::vec3 color = glm::vec3(1.0f);
    if (gmState == MENU) color = glm::vec3(0.5f);

    txt->RenderText(score, glm::vec2(10.0f), 1.0f, color);
}

void Game::Restart()
{
    delete background;
    delete field;
    delete txt;

    delete head;
    delete apple;

    // snake
    for (size_t i = 1; i < snake.size(); ++i)
    {
        delete snake[i];
    }
    // -----
    snake.clear();
    objList.clear();

    gmState = MENU;
    close = false, restart = true, endGame = false;

    Init();
}

void Game::AddSnakePart()
{
    Snake* body = nullptr;

    if (snake.back()->GetDirection() == DOWN) body = new Snake(glm::vec2(snake.back()->GetPos().x, snake.back()->GetPos().y - 10.0f), glm::vec2(30.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));
    else if (snake.back()->GetDirection() == UP) body = new Snake(glm::vec2(snake.back()->GetPos().x, snake.back()->GetPos().y + 10.0f), glm::vec2(30.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));
    else if (snake.back()->GetDirection() == LEFT) body = new Snake(glm::vec2(snake.back()->GetPos().x + 10.0f, snake.back()->GetPos().y), glm::vec2(30.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));
    else if (snake.back()->GetDirection() == RIGHT) body = new Snake(glm::vec2(snake.back()->GetPos().x - 10.0f, snake.back()->GetPos().y), glm::vec2(30.0f), 100.0f, 0.0f, glm::vec3(0.5f, 1.0f, 0.75f));

    if (body != nullptr) {
        body->SetTexture(ResourceManager::GetTexture("body"));
        snake.push_back(body);
        objList.push_back(body);
    }
}

bool Game::TailCollision()
{
    std::vector<bool> col;
    for (size_t i = 1; i < snake.size(); ++i)
    {
        col.push_back(snake[i]->PointCollision( head->GetNosePoint() ));
    }

    return std::any_of(begin(col), end(col), [](bool collision){
        return collision == true;
    });
}

Game::~Game()
{
    delete background;
    delete field;
    delete txt;
    
    delete head;
    delete apple;

    // snake
    for (size_t i = 1; i < snake.size(); ++i)
    {
        delete snake[i];
    }

    snake.clear();
    objList.clear();
    // -----
}
