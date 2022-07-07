#include "GameInputHandler.h"
#include "GameScreen.h"
#include "SoundEngine.h"


class BulletSpawner;

void GameInputHandler::initialise()
{

}

void GameInputHandler::handleGamepad()
{

}

void GameInputHandler::handleKeyPressed(sf::Event& event, sf::RenderWindow& window)
{
    switch (event.key.code) {
        case sf::Keyboard::Escape:
            SoundEngine::playClick();
            getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
            break;
        case sf::Keyboard::Left:
            m_PUC->moveLeft();
            break;
        case sf::Keyboard::Right:
            m_PUC->moveRight();
            break;
        case sf::Keyboard::Up:
            m_PUC->moveUp();
            break;
        case sf::Keyboard::Down:
            m_PUC->moveDown();
            break;
    }
}

void GameInputHandler::handleKeyReleased(sf::Event& event, sf::RenderWindow& window)
{
    switch (event.key.code) {
        case sf::Keyboard::Left:
            m_PUC->stopLeft();
            break;
        case sf::Keyboard::Right:
            m_PUC->stopRight();
            break;
        case sf::Keyboard::Up:
            m_PUC->stopUp();
            break;
        case sf::Keyboard::Down:
            m_PUC->stopDown();
            break;
        case sf::Keyboard::Space:
            SoundEngine::playShoot();
            sf::Vector2f spawnLocation;
            spawnLocation.x = m_PTC->getLocation().x + m_PTC->getSize().x / 2;
            spawnLocation.y = m_PTC->getLocation().y;
            static_cast<GameScreen*>(getParentScreen())->spawnBullet(spawnLocation, true);
            break;
    }

}
