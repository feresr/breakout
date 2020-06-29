#include "BallObject.h"

BallObject::BallObject()
        : GameObject(), radius(12.5f), stuck(false)  { }

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
        : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity), radius(radius), stuck(false) { }



glm::vec2 BallObject::Move(float dt, unsigned int win_width) {

    if (!stuck) {
        Position += Velocity * dt;
        if (Position.x  < 0.0f) {
            Velocity.x = -Velocity.x;
            Position.x = 0.0f;
        } else if (Position.x + Size.x >= win_width) {
            Velocity.x = -Velocity.x;
            Position.x = win_width - Size.x;
        }

        if (Position.y <= 0.0f) {
            Velocity.y = -Velocity.y;
            Position.y = 0.0f;
        }
    }
    return Position;
}


void BallObject::Reset(glm::vec2 position, glm::vec2 velocity) {
    this->Position = position;
    this->Velocity = velocity;
    this->stuck = true;
}
