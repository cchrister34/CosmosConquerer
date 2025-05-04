#pragma once
#include "GameObject.h"
#include "pickuptypes.h"
#include "Spaceship.h"

class GameManager : public GameObject
{
public:
    GameManager(ObjectType objType);
    void Initialise();
    void Update(double frametime)override;
    void Render()override;
    void HandleEvent(Event evt)override;
private:
    int m_score;
    int m_lives;
    PictureIndex m_livesImage;
    PictureIndex m_speedImage;
    PictureIndex m_shootImage;
    PickUpType m_collectedPickup;
    bool m_hasPickup;
    Spaceship* m_respawnedSpaceship;
    double m_dynamicShipHealth;
    Rectangle2D m_healthBar;
    Rectangle2D m_healthBarBackground;
    double m_healthBarWidth;
};
