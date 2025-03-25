#include "Spaceship.h"
#include "HtKeyboard.h"
#include "HtCamera.h"
#include "Bullet.h"
#include "Flare.h"
#include "ObjectManager.h"
#include "Explosion.h"

//Constants
const double CAMERA_VELOCITY = 3.0;
const double CAMERA_FRICTION = 2.0;
const double THRUST = 100.0;
const int ROTATION_SPEED = 120;
const double ANGULAR_FRICTION = 0.4;
const double BULLET_DELAY = 0.3;
const double SHIP_SIZE = 1.25;
const double SHIP_ANGLE = 90;
const double FRICTION_STRENGTH = 0.5;
const double BULLET_MAGNITUDE = 60;
const double BULLET_SPEED = 800.0;
const double FLARE_DELAY = 0.5;
const double FLARE_MAGNITUTE = -60;
const int TOPBORDER = 1000;
const int BOTTOMBORDER = -1000;
const int BORDERLEFT = -250;
const int BORDERRIGHT = 8350;
const std::string SHIP_IMAGE = "assets/spaceship.png"; //Cannot use const char* because of one definition rule 
const std::string ENGINE_SOUND = "assets/thrustloop.wav";
const std::string BULLET_SOUND = "assets/zap.wav";
const std::string EXPLOSION_SOUND = "assets/explosion1.wav";

Spaceship::Spaceship(ObjectType objType) : GameObject(objType)
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
           m_acceleration.setBearing(m_angle, THRUST);
           m_acceleration = m_acceleration - m_velocity * FRICTION_STRENGTH;
           m_velocity = m_velocity + m_acceleration * frametime;
           m_position = m_position + m_velocity * frametime;
        }
    }
    else if (isEnginePlaying)
    {
        HtAudio::instance.Stop(m_engineSoundChannel);
        isEnginePlaying = false;
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
        m_shootdelay = BULLET_DELAY;
        m_bulletSoundChannel = HtAudio::instance.Play(m_bulletSound);
    }

    //Flares
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_F) && m_flareDelay < 0)
    {
        m_flarePosition.setBearing(m_angle, FLARE_MAGNITUTE);
        m_flarePosition = m_flarePosition + m_position;
        Flare* pFlare;
        pFlare = new Flare;
        Vector2D flarePosition = m_flarePosition;
        m_flareSpeed = m_flareSpeed + m_velocity;
        Vector2D flareVelocity = m_flareSpeed;
        pFlare->Initialise(flarePosition, flareVelocity);
        ObjectManager::instance.AddItem(pFlare);
        m_flareDelay = FLARE_DELAY;
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
        Explosion* p_Explosion = new Explosion();
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
    m_position.set(0, 0);
    m_velocity.set(0, 0);
    LoadImage(SHIP_IMAGE.c_str()); //c_str used to convert sting to const char
    m_scale = SHIP_SIZE; 
    m_angle = SHIP_ANGLE;
    m_cameraPosition.set(0, 0);
    m_cameraVelocity.set(0, 0);
    m_engineSound = HtAudio::instance.LoadSound(ENGINE_SOUND.c_str());

    m_shootdelay = BULLET_DELAY;
    m_bulletSound = HtAudio::instance.LoadSound(BULLET_SOUND.c_str());
    m_explosionBang = HtAudio::instance.LoadSound(EXPLOSION_SOUND.c_str());

    m_flareDelay = FLARE_DELAY;

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

