//
// Created by Fernando Raviola on 28/06/2020.
//

#include <resource_manager.h>
#include <SpriteRenderer.h>
#include <GLFW/glfw3.h>
#include <BallObject.h>
#include "Game.h"

SpriteRenderer* renderer;

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(40.0f, -20.0f); // Radius of the ball object
const float BALL_RADIUS = 12.5f;

GameObject* player;
BallObject* ball;

void Game::ProcessInput(float dt) {
    if (State == GAME_ACTIVE) {
        float velocity = PLAYER_VELOCITY * dt;
        if (Keys[GLFW_KEY_A]) {
            if (player->Position.x >= 0.0f) {
                player->Position.x -= velocity;
            }
        }
        if (Keys[GLFW_KEY_D]) {
            if (player->Position.x <= Width - player->Size.x) {
                player->Position.x += velocity;
            }
        }
    }
}

void Game::Update(float dt) {
    ball->Move(dt, Width);
}

void Game::Render() {
    if (State == GAME_ACTIVE) {
        renderer->DrawSprite(
                ResourceManager::GetTexture("background"),
                glm::vec2(00.0f, 00.0f),
                glm::vec2(Width, Height),
                0.0f);
        Levels[level].Draw(*renderer);
        player->Draw(*renderer);
        ball->Draw(*renderer);
    }
}

Game::Game(unsigned int width, unsigned int height) : Width{width}, Height{height} {}


Game::~Game() {
    delete renderer;
    delete player;
    delete ball;
}

void Game::Init() {

    ResourceManager::LoadShader("shaders/sprite.vsh", "shaders/sprite.fsh", nullptr, "sprite");

    //configure shader
    glm::mat4 projection = glm::ortho(0.0f,
                                      static_cast<float>(Width),
                                      static_cast<float>(Height), 0.0f, -1.f, 1.f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);

    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    ResourceManager::LoadTexture("textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("textures/block.png", false, "block");
    ResourceManager::LoadTexture("textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");

    GameLevel one;
    one.Load("levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two;
    two.Load("levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three;
    three.Load("levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four;
    four.Load("levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->level = 0;

    glm::vec2 playerPos = glm::vec2(Width / 2.0f - PLAYER_SIZE.x / 2.0f, Height - PLAYER_SIZE.y);
    player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
    ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
}
