#include "GameManager.h"
#include "Spaceship.h"
#include "ObjectManager.h"
#include "HtCamera.h"


GameManager::GameManager() : GameObject(ObjectType::GAMEMANAGER)
{
}

void GameManager::Initialise()
{
    m_score = 0;
    m_lives = 3;

    m_livesImage = HtGraphics::instance.LoadPicture("assets/spaceship.png"); 
    SetHandleEvents();
}

void GameManager::Update(double frametime)
{
}

void GameManager::Render()
{
    Vector2D topLeft(-1600, 920);
    HtCamera::instance.UseCamera(false);
    HtGraphics::instance.WriteIntAligned(topLeft, m_score, HtGraphics::WHITE, 2, 1.25);
    HtCamera::instance.UseCamera(true);

    Vector2D livesPos(1100, 950);
    int lifeSpace = 100;

    HtCamera::instance.UseCamera(false);
    for (int i = 0; i < m_lives; i++)
    {
        HtGraphics::instance.DrawAt(livesPos, m_livesImage);
        livesPos.XValue += lifeSpace;
    }
    HtCamera::instance.UseCamera(true);
}

void GameManager::HandleEvent(Event evt)
{
    if (evt.type == EventType::OBJECTDESTROYED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::ROCK) //evt.Psource && is a check that it is not a null ptr
        {
            m_score += 100;
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


