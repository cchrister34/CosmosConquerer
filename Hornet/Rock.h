#pragma once
#include "GameObject.h"
class Rock : public GameObject
{
public:
    Rock(ObjectType objType);
    void Update(double frametime) override;
    void ProcessCollision(GameObject& other) override;
    void Initialise();
    IShape2D& GetCollisionShape() override;
private:
    Vector2D m_velocity;
    Circle2D m_collisionShape;
};

