#pragma once
#include "GameObject.h"
#include "HtAudio.h"

class Spaceship;

class EnemyShip : public GameObject
{
public:
    EnemyShip(ObjectType objType);
    void Initialise();
    void Update(double frametime);
    void FindPlayer(Spaceship* pTarget);
    void Shoot();
    void Explode();
    IShape2D& GetCollisionShape() override;
    void ProcessCollision(GameObject& other)override;
    void HandleEvent(Event evt)override;
private:
    double m_enemySpawnXpos;
    double m_enemySpawnYpos;
    double m_enemySpeed;
    double m_enemyPosAngle;
    double m_enemyVelAngle;
    Spaceship* m_pTarget;
    bool m_isPlayerInRange;
    double m_distance;
    Vector2D m_direction;
    Vector2D m_playerLocation;
    Vector2D m_velocity;
    Circle2D m_collisionShape;
    double m_shootdelay;
    Vector2D m_bulletPosition;
    Vector2D m_bulletSpeed;
    SoundIndex m_bulletSound;
    int m_bulletSoundChannel;
    SoundIndex m_explosionBang;
    int m_explosionSoundChannel;
    bool m_isBulletSoundPlaying;
};

