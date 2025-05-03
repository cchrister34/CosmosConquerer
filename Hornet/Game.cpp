#include "Game.h"
#include "HtCamera.h"
#include "ObjectManager.h"

void Game::StartOfProgram()
{



    // This makes the operating system's mouse pointer invisible
    // It's usually best to use your own instead.
    HtMouse::instance.SetPointerVisiblity(false);
}

// Use this function to intialise your game objects and load any assets
void Game::StartOfGame()
{
    CreatePlayer();
    CreateRocks();
    CreateGameManager();
    CreateScene();
    CreatePickups();
    CreateMissile();
    CreateTractorBeam();
}

// Function runs each frame.
// "frametime" is the time in seconds since the last call (delta time)
void Game::Update(double frametime)
{
    // In the space below, you can write code to create a game the hard way.
    // To start with, we will use this area, but later will use game objects.




    // The code below runs the managed part of the game engine
    // Best to leave it alone
    ObjectManager::instance.UpdateAll(frametime);
    ObjectManager::instance.ProcessCollisions();
    ObjectManager::instance.RenderAll();
#ifdef _DEBUG
    ObjectManager::instance.CycleDebugObject();
    ObjectManager::instance.RenderDebug();
#endif
    ObjectManager::instance.DeleteInactiveItems();

    // Draws all graphics to the screen. Best not to remove this line.
    HtGraphics::instance.Present();
}

// Function runs when the user pauses the program.
// You may want to stop sound effects.
void Game::OnSuspend()
{
    HtAudio::instance.StopAllChannels();
    HtCamera::instance.UseCamera(false);

    if (pSpaceship)
    {
        pSpaceship->SetFriction(false);
    }

}


// This function runs when the user resumes the game from pause
// You can start sound effects if needed, but it is usually
// best to just let the game create new sounds if needed.
void Game::OnResume()
{
    HtCamera::instance.UseCamera(true);

    if (pSpaceship)
    {
        pSpaceship->SetFriction(true);
    }
}

// You can use this to clear up any memory, if needed
void Game::EndOfGame()
{



    //This line automatically deletes all managed objects
    ObjectManager::instance.DeleteAllObjects();
    pSpaceship = nullptr;
}

void Game::EndOfProgram()
{
}



void Game::CreatePlayer()
{
    pSpaceship = new Spaceship(ObjectType::SPACESHIP);
    pSpaceship->Initialise();
    ObjectManager::instance.AddItem(pSpaceship); //object manager handles deletion and sets the pointer to null.
}

void Game::CreateRocks()
{
    for (Rock* pRock : pTheRocks)
    {
        pRock = new Rock(ObjectType::ROCK);
        pRock->Initialise();
        ObjectManager::instance.AddItem(pRock);
    }
}

void Game::CreateGameManager()
{
    pGameManager = new GameManager(ObjectType::GAMEMANAGER);
    pGameManager->Initialise();
    ObjectManager::instance.AddItem(pGameManager);
}

void Game::CreateScene()
{
    //Scene class hosts the background, tile and tractor beam objects to keep the game loop cleaner
    pScene = new Scene(ObjectType::SCENE);
    pScene->Initialise();
    ObjectManager::instance.AddItem(pScene);
}

void Game::CreatePickups()
{
    PickUp* pSpeedPickup = new PickUp(PickUpType::SPEED);
    pSpeedPickup->Initialise();
    ObjectManager::instance.AddItem(pSpeedPickup);

    PickUp* pFireRatePickup = new PickUp(PickUpType::FIRE_RATE);
    pFireRatePickup->Initialise();
    ObjectManager::instance.AddItem(pFireRatePickup);
}

void Game::CreateMissile()
{
    Missile* pMissile = new Missile(ObjectType::MISSILE);
    pMissile->Initialise();
    pMissile->SetTarget(pSpaceship);
    ObjectManager::instance.AddItem(pMissile);
}

void Game::CreateTractorBeam()
{
    //Ideally this goes in the Scene class
//But since the Tractor beam works by pulling the spaceship it needs to know about pSpaceship
    std::vector<Vector2D> tractorbeamPositions =
    {
        Vector2D(4500, 1000),
        Vector2D(7000, 1000)
    };

    for (const Vector2D& position : tractorbeamPositions)
    {
        TractorBeam* pTractorBeam = new TractorBeam(ObjectType::TRACTORBEAM);
        pTractorBeam->Initialise(position);
        //Very important line, cannot be used in scene.cpp without causing dependencies
       // pTractorBeam->PullTarget(pSpaceship);
        ObjectManager::instance.AddItem(pTractorBeam);
    }
}
