#pragma once
#include "GameObject.h"
class Rock : public GameObject
{
public:
    Rock();
    void Update(double frametime) override;
    void ProcessCollision(GameObject& other) override;
    void Initialise();
    IShape2D& GetCollisionShape() override;
    void Initialise(Vector2D rockSize, Vector2D rockVelocity, double size);
private:
    Vector2D m_velocity;
    Circle2D m_collisionShape;
};

