#pragma once
#include "GameObject.h"
#include "Spaceship.h"


class EnemyShip : public GameObject
{
public:
    EnemyShip();
    void Initialise();
    void Update(double frametime);
    void FindPlayer(Spaceship* pTarget);
    void ProcessCollision(GameObject& other)override;
    void HandleEvent(Event evt)override;
private:
    Spaceship* m_pTarget;
    double m_direction;
    Vector2D m_playerLocation;
    Vector2D m_velocity;
    bool m_isPlayerInRange;
    Circle2D m_collisionShape;
};

