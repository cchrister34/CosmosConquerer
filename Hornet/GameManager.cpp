 #include "GameManager.h"
#include "Spaceship.h"
#include "ObjectManager.h"
#include "HtCamera.h"
#include "PickUp.h"
#include "Missile.h"

//Constants
const int START_SCORE = 0;
const int START_LIVES = 3;
const double SHIP_HEALTH = 100;
const double MAX_HP_BAR_WIDTH = 400;
const double HP_BAR_TOP = 970;
const double HP_BAR_BOTTOM = 940;
const double HP_BAR_LEFT = -200;
const Vector2D TOP_LEFT(-1600, 920);
const int LIVES_GAP = 100;
const int FONT = 2;
const double FONT_SIZE = 1.25;
const int ROCK_SCORE_INCREASE = 100;
const int MISSILE_SCORE_INCREASE = 500;
const int TRACTOR_BEAM_SCORE_INCREASE = 150;
const std::string SHIP_IMAGE = "assets/spaceship.png";
const std::string SPEED_PICKUP_IMAGE = "assets/powerup1.png";
const std::string SHOOT_PICKUP_IMAGE = "assets/powerup2.png";


GameManager::GameManager(ObjectType objType)
{
}

void GameManager::Initialise()
{
    m_score = START_SCORE;
    m_lives = START_LIVES;
    m_dynamicShipHealth = SHIP_HEALTH;
    
    m_hasPickup = false;
    m_collectedPickup = PickUpType::NONE;

    m_livesImage = HtGraphics::instance.LoadPicture(SHIP_IMAGE.c_str()); 
    m_speedImage = HtGraphics::instance.LoadPicture(SPEED_PICKUP_IMAGE.c_str());
    m_shootImage = HtGraphics::instance.LoadPicture(SHOOT_PICKUP_IMAGE.c_str());
    SetDrawDepth(2);
    SetHandleEvents();
}

void GameManager::Update(double frametime)
{
}

void GameManager::Render()
{
    HtCamera::instance.UseCamera(false);
    HtGraphics::instance.WriteIntAligned(TOP_LEFT, m_score, HtGraphics::WHITE, FONT, FONT_SIZE);
    HtCamera::instance.UseCamera(true);

    Vector2D livesPos(1100, 950); //not a const because it needs to be changed from certain events
    HtCamera::instance.UseCamera(false);
    for (int i = 0; i < m_lives; i++)
    {
        HtGraphics::instance.DrawAt(livesPos, m_livesImage);
        livesPos.XValue += LIVES_GAP;
    }
    HtCamera::instance.UseCamera(true);

    //HealthBar
    double width = MAX_HP_BAR_WIDTH;
    double top = HP_BAR_TOP;
    double bottom = HP_BAR_BOTTOM;
    double left = -HP_BAR_LEFT;
    double right = left + (m_dynamicShipHealth / SHIP_HEALTH) * width;
    m_healthBar.PlaceAt(top, left, bottom, right);

    HtCamera::instance.UseCamera(false);
    HtGraphics::instance.FillRect(m_healthBar, HtGraphics::LIGHTGREEN);
    HtCamera::instance.UseCamera(true);


    //Pickup
    if (m_hasPickup)
    {
        Vector2D pickupPos(1000, 950);
        if (m_collectedPickup == PickUpType::SPEED)
        {
            HtCamera::instance.UseCamera(false);
            HtGraphics::instance.DrawAt(pickupPos, m_speedImage);
            HtCamera::instance.UseCamera(true);
        }
        else if (m_collectedPickup == PickUpType::FIRE_RATE)
        {
            HtCamera::instance.UseCamera(false);
            HtGraphics::instance.DrawAt(pickupPos, m_shootImage);
            HtCamera::instance.UseCamera(true);
        }
    }
}

void GameManager::HandleEvent(Event evt)
{
    if (evt.type == EventType::OBJECTDESTROYED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::ROCK) //evt.Psource && is a check that it is not a null ptr
        {
            m_score += ROCK_SCORE_INCREASE;
        }
    }

    if (evt.type == EventType::OBJECTCOLLECTED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::PICKUP)
        {
            PickUp* pPickUp = static_cast<PickUp*>(evt.pSource);
            m_collectedPickup = pPickUp->GetPickUpType();
            m_hasPickup = true;
        }
    }

    if (evt.type == EventType::PICKUPUSED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::SPACESHIP)
        {
            m_hasPickup = false;
            m_collectedPickup = PickUpType::NONE;
        }
    }

    if (evt.type == EventType::SHIPDAMAGED)
    {
        Spaceship* pShip = dynamic_cast<Spaceship*>(evt.pSource);
        if (pShip)
        {
            m_dynamicShipHealth = pShip->GetHealth();
        }
    }

    if (evt.type == EventType::OBJECTDESTROYED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::SPACESHIP)
        {
            Spaceship* pShip = dynamic_cast<Spaceship*>(evt.pSource);
            if (pShip && pShip->IsDead())
            {
                if (m_lives > 0)
                {
                    Spaceship* pSpaceship = nullptr;
                    pSpaceship = new Spaceship(ObjectType::SPACESHIP);
                    pSpaceship->Initialise();
                    ObjectManager::instance.AddItem(pSpaceship);
                    m_lives -= 1;
                    //Assign the new spaceship object to a member variable
                    //If the spaceship was destroyed before the missile timer ran out, the missiles would no longer spawn
                    m_respawnedSpaceship = pSpaceship;
                    //Create an event for the respawned spaceship for listeners such as the tractor beam
                    Event evt;
                    evt.type = EventType::OBJECTCREATED;
                    evt.pSource = pSpaceship;
                    ObjectManager::instance.HandleEvent(evt);

                    //Safety check to ensure the object is active before creating a missile
                    if (m_respawnedSpaceship != nullptr)
                    {
                        Missile* pMissile = new Missile(ObjectType::MISSILE);
                        pMissile->Initialise();
                        //Assign the missile to the most recently created spaceship object
                        pMissile->SetTarget(m_respawnedSpaceship);
                        ObjectManager::instance.AddItem(pMissile);
                    }
                }
            }
        }
    }


    if (evt.type == EventType::OBJECTDESTROYED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::MISSILE)
        {
            m_score += MISSILE_SCORE_INCREASE;
        }
    }

    if (evt.type == EventType::OBJECTDESTROYED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::TRACTORBEAM)
        {
            m_score += TRACTOR_BEAM_SCORE_INCREASE;
        }
    }

}


