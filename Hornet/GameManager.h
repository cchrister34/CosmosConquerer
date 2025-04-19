#pragma once
#include "GameObject.h"
#include "pickuptypes.h"

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
};
