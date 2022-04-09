#include "BulletSpawner.h"
#include "InvaderUpdateComponent.h"
#include "SoundEngine.h"
#include "WorldState.h"


void InvaderUpdateComponent::update(float fps)
{
    if (m_MovingRight) {
        m_TC->getLocation().x += m_Speed * fps;
    } else {
        m_TC->getLocation().x -= m_Speed * fps;
    }

    sf::Vector2f location = m_TC->getLocation();
    sf::Vector2f size = m_TC->getSize();
    m_RCC->setOrMoveCollider(location.x, location.y, size.x, size.y);
    m_TimeSinceLastShot += fps;

    sf::Vector2f playerLocation = m_PlayerTC->getLocation();
    sf::Vector2f playerSize = m_PlayerTC->getSize();
    if ((location.x + size.x / 2) > (playerLocation.x - m_AccuracyModifier) &&
        (location.x + size.x / 2) < (playerLocation.x + playerSize.x + m_AccuracyModifier))
    {
        if (m_TimeSinceLastShot > m_TimeBetweenShots) {
            SoundEngine::playShoot();
            sf::Vector2f spawnLocation(location.x + size.x / 2, location.y + size.y);
            m_BulletSpawner->spawnBullet(spawnLocation, false);
            srand(m_RandSeed);
            m_TimeBetweenShots = (rand() % 10 + 1) / WorldState::WAVE_NUMBER;
            m_TimeSinceLastShot = 0.0f;
        }
    }
}

void InvaderUpdateComponent::dropDownAndReverse()
{
    m_MovingRight = !m_MovingRight;
    m_TC->getLocation().y += m_TC->getSize().y;
    int numInvaders = WorldState::NUM_INVADERS_AT_START - WorldState::NUM_INVADERS;
    m_Speed += WorldState::WAVE_NUMBER + numInvaders * m_SpeedModifier;
}

bool InvaderUpdateComponent::isMovingRight()
{
    return m_MovingRight;
}

void InvaderUpdateComponent::initialiseBulletSpawner(BulletSpawner* bulletSpawner, int randSeed)
{
    m_BulletSpawner = bulletSpawner;
    m_RandSeed = randSeed;

    srand(m_RandSeed);
    m_TimeBetweenShots = rand() % 15 + m_RandSeed;
    m_AccuracyModifier = rand() % 2;
    m_AccuracyModifier += 0 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10);
}
