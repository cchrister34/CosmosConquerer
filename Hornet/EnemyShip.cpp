#include "EnemyShip.h"

//Constants
const std::string ENEMY_SHIP_IMAGE = "assets/enemyship.png";


EnemyShip::EnemyShip()
{
    m_pTarget = nullptr;
}

void EnemyShip::Initialise()
{
}

void EnemyShip::Update(double frametime)
{
}

void EnemyShip::FindPlayer(Spaceship* pTarget)
{
}

void EnemyShip::ProcessCollision(GameObject& other)
{
}

void EnemyShip::HandleEvent(Event evt)
{
}

