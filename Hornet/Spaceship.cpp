#include "Spaceship.h"
#include "HtKeyboard.h"
#include "HtCamera.h"
#include "Bullet.h"
#include "Flare.h"
#include "ObjectManager.h"
#include "Explosion.h"

//Constants
const Vector2D START_SPAWN_POS(0, 0);
const Vector2D START_VELOCITY(0, 0);
const Vector2D START_CAMERA_POS(0, 0);
const Vector2D START_CAMERA_VELOCITY(0, 0);
const Vector2D STUCK_VELOCITY(0, 0);
const double CAMERA_VELOCITY = 3.0;
const double CAMERA_FRICTION = 2.0;
const double THRUST_STRENGTH = 90.0;
const int ROTATION_SPEED = 120;
const double ANGULAR_FRICTION = 0.4;
const double BULLET_DELAY = 0.3;
const double SHIP_SIZE = 1.25;
const double SHIP_ANGLE = 90;
const double FRICTION_STRENGTH = 0.5;
const double BULLET_MAGNITUDE = 60;
const double BULLET_SPEED = 800.0;
const double FLARE_DELAY = 1;
const double FLARE_MAGNITUTE = -20;
const int FLARE_AMOUNT = 3;
const double FLARE_SPREAD = 20;
const double FLARE_SPEED = 200.0;
const int TOPBORDER = 1000;
const int BOTTOMBORDER = -1000;
const int BORDERLEFT = -250;
const int BORDERRIGHT = 8350;
const double SPEED_PICKUP_MULTIPLIER = 1.5;
const double SHOOT_PICKUP_MULTIPLIER = 2.0;
const double PICK_UP_TIMER = 5.0;
const double BASE_PICKUP_MULTIPLIER = 1.0;
const double REDUCED_PULL_SPEED = 10;
const double TRACTOR_BEAM_SPEED_REDUCTION = 0.3;
const std::string SHIP_IMAGE = "assets/spaceship.png"; //Cannot use const char* because of one definition rule 
const std::string ENGINE_SOUND = "assets/thrustloop.wav";
const std::string BULLET_SOUND = "assets/zap.wav";
const std::string EXPLOSION_SOUND = "assets/explosion1.wav";
const std::string FLARE_SOUND = "assets/flare.flac";

Spaceship::Spaceship(ObjectType objType) : GameObject(ObjectType::SPACESHIP)
{
}

void Spaceship::Update(double frametime)
{
    m_position = m_position + m_velocity * frametime;
    m_shootdelay -= frametime;
    m_flareDelay -= frametime;

    //Camera
    //Since the game is a sidescroller the camera boundaries should match that of the screen which in this case is between -1000 and 1000
    m_topCameraBorder = HtCamera::instance.GetTopOfCameraArea();
    m_bottomCameraBorder = HtCamera::instance.GetBottomOfCameraArea();

    if (m_topCameraBorder > TOPBORDER)
    {
        m_cameraPosition.YValue += TOPBORDER - m_topCameraBorder;
    }
    if (m_bottomCameraBorder < BOTTOMBORDER)
    {
        m_cameraPosition.YValue -= m_bottomCameraBorder - BOTTOMBORDER;
    }

    m_cameraVelocity = m_cameraVelocity + (m_position - m_cameraPosition) * CAMERA_VELOCITY * frametime;
    m_cameraVelocity = m_cameraVelocity - m_cameraVelocity * CAMERA_FRICTION * frametime;
    m_cameraPosition = m_cameraPosition + m_cameraVelocity * frametime;
    HtCamera::instance.PlaceAt(Vector2D(m_cameraPosition));


    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W))
    {
        //Sound
        if (!isEnginePlaying)
        {
            m_engineSoundChannel = HtAudio::instance.Play(m_engineSound, true);
            isEnginePlaying = true;
        }

        //Friction;
        if (m_isFrictionActive) //Used to prevent the effects of friction occuring when game is paused.
        {
            m_thrust.setBearing(m_angle, THRUST_STRENGTH * m_speedMultiplier);
            m_velocity = m_velocity + m_thrust * frametime;
        }
    }
    else if (isEnginePlaying)
    {
        HtAudio::instance.Stop(m_engineSoundChannel);
        isEnginePlaying = false;
    }

    if (m_isFrictionActive)
    {
        m_friction = m_velocity * FRICTION_STRENGTH;
        m_velocity = m_velocity - m_friction * frametime;
        m_position = m_position + m_velocity * frametime;
    }

    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_A))
    {
        m_angularVelocity -= ROTATION_SPEED * frametime;
    }

    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_D))
    {
        m_angularVelocity += ROTATION_SPEED * frametime;
    }

    m_angularVelocity -= m_angularVelocity * ANGULAR_FRICTION * frametime;
    m_angle += m_angularVelocity * frametime;

    //Bullets
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_SPACE) && m_shootdelay < 0)
    {
        m_bulletPosition.setBearing(m_angle, BULLET_MAGNITUDE);
        m_bulletPosition = m_bulletPosition + m_position;
        Bullet* pBullet;
        pBullet = new Bullet;
        Vector2D bulletPosition = m_bulletPosition;
        m_bulletSpeed.setBearing(m_angle, BULLET_SPEED);
        m_bulletSpeed = m_bulletSpeed + m_velocity;
        Vector2D bulletVelocity = m_bulletSpeed;
        pBullet->Initialise(bulletPosition, bulletVelocity);
        ObjectManager::instance.AddItem(pBullet);
        m_shootdelay = m_dynamicbulletDelay;
        m_bulletSoundChannel = HtAudio::instance.Play(m_bulletSound);
    }

    //Flares
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_F) && m_flareDelay < 0)
    {
        //Flares or stored in this vector, will be useful later for programming homing missile
        std::vector<Flare*> flares;

        //sets the offset of the flare so they dont appear from the middle of the spaceship
        m_flareOffset.setBearing(m_angle, FLARE_MAGNITUTE);
        //adds the offset to the position of the ship
        m_flareSpawn = m_position + m_flareOffset;

        //Loop through flares
        for (int i = 0; i < FLARE_AMOUNT; i++)
        {
            //finds the angle of the ship and loops through the flares and adds flare spread between each flare
            m_flareAngle = m_angle + (i - 1) * FLARE_SPREAD;

            m_flareVelocity;
            m_flareVelocity.setBearing(m_flareAngle, FLARE_SPEED);
            //flares should travel in the opposite direction of the spaceship
            m_flareVelocity = m_flareVelocity - m_velocity;

            Flare* pFlare = new Flare(ObjectType::FLARE);
            pFlare->Initialise(m_flareSpawn, m_flareVelocity);
            flares.push_back(pFlare);
        }

        for (Flare* flare : flares)
        {
            ObjectManager::instance.AddItem(flare); //Still adding to object manager to ensure deletion of the object
        }
        m_flareDelay = FLARE_DELAY;
        m_flareSoundChannel = HtAudio::instance.Play(m_flareSound);
    }
     
    //PickUp
        if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_E))
        {
            UsePickUp();
        }

        if (m_pickupTimer > 0)
        {
            m_pickupTimer -= frametime;
        if (m_pickupTimer <= 0)
        {
            m_dynamicbulletDelay = BULLET_DELAY;
            m_speedMultiplier = BASE_PICKUP_MULTIPLIER;
        }
    }

    //Wrapping 
    if (m_position.XValue < BORDERLEFT)
    {
        m_velocity.XValue = -m_velocity.XValue;
    }
    else if (m_position.XValue > BORDERRIGHT)
    {
        m_velocity.XValue = -m_velocity.XValue;
    }

    if (m_position.YValue > TOPBORDER)
    {
        m_velocity.YValue = -m_velocity.YValue;
    }
    else if (m_position.YValue < BOTTOMBORDER)
    {
        m_velocity.YValue = -m_velocity.YValue;
    }

    m_collisionShape.PlaceAt(m_position, SHIP_SIZE);
}


void Spaceship::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::ROCK)
    {
        Deactivate();
        HtAudio::instance.Stop(m_engineSoundChannel);
        Explosion* p_Explosion = new Explosion(ObjectType::EXPLOSION);
        p_Explosion->Initialise(m_position);
        ObjectManager::instance.AddItem(p_Explosion);
        m_explosionSoundChannel = HtAudio::instance.Play(m_explosionBang);
        Event evt;
        evt.type = EventType::OBJECTDESTROYED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }

    if (other.GetType() == ObjectType::TILE)
    {
        Deactivate();
        HtAudio::instance.Stop(m_engineSoundChannel);
        Explosion* p_Explosion = new Explosion(ObjectType::EXPLOSION);
        p_Explosion->Initialise(m_position);
        ObjectManager::instance.AddItem(p_Explosion);
        m_explosionSoundChannel = HtAudio::instance.Play(m_explosionBang);
        Event evt;
        evt.type = EventType::OBJECTDESTROYED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }

    if (other.GetType() == ObjectType::MISSILE)
    {
        Deactivate();
        HtAudio::instance.Stop(m_engineSoundChannel);
        Explosion* p_Explosion = new Explosion(ObjectType::EXPLOSION);
        p_Explosion->Initialise(m_position);
        ObjectManager::instance.AddItem(p_Explosion);
        m_explosionSoundChannel = HtAudio::instance.Play(m_explosionBang);
        Event evt;
        evt.type = EventType::OBJECTDESTROYED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }
}

void Spaceship::Initialise()
{
    m_position.set(START_SPAWN_POS);
    m_velocity.set(START_VELOCITY);
    LoadImage(SHIP_IMAGE.c_str()); //c_str used to convert sting to const char
    m_scale = SHIP_SIZE; 
    m_angle = SHIP_ANGLE;
    m_cameraPosition.set(START_CAMERA_POS);
    m_cameraVelocity.set(START_CAMERA_VELOCITY);
    m_engineSound = HtAudio::instance.LoadSound(ENGINE_SOUND.c_str());

    //Bullet
    m_shootdelay = BULLET_DELAY;
    m_bulletSound = HtAudio::instance.LoadSound(BULLET_SOUND.c_str());

    //Explosion
    m_explosionBang = HtAudio::instance.LoadSound(EXPLOSION_SOUND.c_str());

    //Flares
    m_flareDelay = FLARE_DELAY;
    m_flareSound = HtAudio::instance.LoadSound(FLARE_SOUND.c_str());

    //Pickups
    m_dynamicbulletDelay = BULLET_DELAY;
    m_speedMultiplier = BASE_PICKUP_MULTIPLIER;
    m_shootMultiplier = BASE_PICKUP_MULTIPLIER;

    SetCollidable();
}

void Spaceship::SetFriction(bool active)
{
    m_isFrictionActive = active;
}


IShape2D& Spaceship::GetCollisionShape()
{
    return m_collisionShape;
}

//This function stores the correct collected pick up
void Spaceship::CollectPickup(PickUpType type)
{
    m_collectedPickup = type;
    m_hasPickup = true;
}

void Spaceship::UseSpeedBoost()
{
    m_speedMultiplier = SPEED_PICKUP_MULTIPLIER;
    m_pickupTimer = PICK_UP_TIMER;
}

void Spaceship::UseShootBoost()
{
    m_dynamicbulletDelay = BULLET_DELAY / SHOOT_PICKUP_MULTIPLIER;
    m_pickupTimer = PICK_UP_TIMER;
}

//This function checks if a pick up has been collected and then accordindly assigns the corresponding function.
void Spaceship::UsePickUp()
{
    if (!m_hasPickup)
        return;
    switch (m_collectedPickup)
    {
    case PickUpType::SPEED:
        UseSpeedBoost();
        break;
    case PickUpType::FIRE_RATE:
        UseShootBoost();
        break;
    }

    m_hasPickup = false;
}

void Spaceship::TractorBeamPull(Vector2D pull)
{
    m_velocity += pull;
}

