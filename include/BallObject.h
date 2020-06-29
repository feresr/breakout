#pragma once

#include "GameObject.h"

class BallObject : public GameObject {

public:
    float radius;
    bool stuck;

    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity,
               Texture2D sprite);

    glm::vec2 Move(float dt, unsigned int win_width);
    void Reset(glm::vec2 position, glm::vec2 velocity);
};