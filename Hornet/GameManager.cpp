#include "GameManager.h"
#include "Spaceship.h"
#include "ObjectManager.h"
#include "HtCamera.h"

//Constants
const int START_SCORE = 0;
const int START_LIVES = 3;
const Vector2D TOP_LEFT(-1600, 920);
const int LIVES_GAP = 100;
const int FONT = 2;
const double FONT_SIZE = 1.25;
const int ROCK_SCORE_INCREASE = 100;
const std::string SHIP_IMAGE = "assets/spaceship.png";


GameManager::GameManager(ObjectType objType)
{
}

void GameManager::Initialise()
{
    m_score = START_SCORE;
    m_lives = START_LIVES;

    m_livesImage = HtGraphics::instance.LoadPicture(SHIP_IMAGE.c_str()); 
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

    if (evt.type == EventType::OBJECTDESTROYED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::SPACESHIP)
        {
            if (m_lives > 0)
            {
                Spaceship* pSpacehip = nullptr;
                pSpacehip = new Spaceship(ObjectType::SPACESHIP);
                pSpacehip->Initialise();
                ObjectManager::instance.AddItem(pSpacehip);
                m_lives -= 1;

            }
        }
    }
}


