#pragma once
#include "GameObject.h"

class Spaceship : public GameObject
{
public:
    Spaceship();
    void Update(double frametime) override;
    void ProcessCollision(GameObject& other) override;
    void Initialise();
private:
    Vector2D m_velocity;
};

