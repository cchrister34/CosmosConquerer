#pragma once
#include "GameObject.h"
#include "Spaceship.h"
class Missile : public GameObject
{
public:
    Missile(ObjectType objType);
    void Initialise();
    void SetTarget(Spaceship* pTarget);
    void Update(double frametime);
    void HandleEvent(Event evt) override;
    void ProcessCollision(GameObject& other) override;
private:
    Spaceship* m_pTarget;
    double m_direction;
    Vector2D m_targetLocation;
    Vector2D m_velocity;
    double m_spawnDelay;
    bool m_hasMissileSpawned;
};

