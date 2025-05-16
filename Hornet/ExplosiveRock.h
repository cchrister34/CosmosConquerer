#pragma once
#include "GameObject.h"
#include "HtAudio.h"

class Spaceship;

class ExplosiveRock : public GameObject
{
public:
    ExplosiveRock(ObjectType objType);
    void Initialise();
    void FindPlayer(Spaceship* pTarget);
    void Update(double frametime);
    void ProcessCollision(GameObject& other)override;
    IShape2D& GetCollisionShape() override;
    void HandleEvent(Event evt)override;
    void Explode();
private:
    Vector2D m_velocity;
    Circle2D m_collisionShape;
    double m_explosiveRockXpos;
    double m_explosiveRockYpos;
    double m_explosiveRockSpeed;
    double m_explosiveRockVelocityAngle;
    Spaceship* m_pTarget;
    Vector2D m_playerLocation;
    double m_distance;
    bool m_isActive;
    SoundIndex m_explosionSound;
    int m_explosionSoundChannel;
    bool m_isExplosionSoundPlaying;
};

