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
    void DisplayGameOver() const;
    void DisplayLevelComplete() const;
private:
    FontIndex m_MessageFont;
    int m_score;
    int m_lives;
    PictureIndex m_livesImage;
    PictureIndex m_speedImage;
    PictureIndex m_shootImage;
    PictureIndex m_healthImage;
    PickUpType m_collectedPickup;
    bool m_hasPickup;
    double m_dynamicShipHealth;
    Rectangle2D m_healthBar;
    Rectangle2D m_healthBarBackground;
    Vector2D m_healthBarPos;
    double m_healthBarWidth;
    bool m_isGameOver;
    bool m_isGameWon;
    Spaceship* m_respawnedSpaceship;
    bool m_shipHasBeenHit;
    int m_displayHealth;
    Vector2D m_healthNumberPos;
};
