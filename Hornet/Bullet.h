#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
    Bullet();
    void Update(double frametime) override;
    void ProcessCollision(GameObject& other) override;
    void Initialise(Vector2D position, Vector2D velocity);
    IShape2D& GetCollisionShape() override;
private:
    Vector2D m_velocity;
    double m_lifetime;
    Circle2D m_collisionArea;
};
