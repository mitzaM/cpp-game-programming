#include "GameInputHandler.h"
#include "GameScreen.h"
#include "SoundEngine.h"


void GameInputHandler::initialise()
{

}

void GameInputHandler::handleGamepad()
{

}

void GameInputHandler::handleKeyPressed(sf::Event& event, sf::RenderWindow& window)
{
    if (event.key.code == sf::Keyboard::Escape) {
        SoundEngine::playClick();
        getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
    }
}

void GameInputHandler::handleKeyReleased(sf::Event& event, sf::RenderWindow& window)
{

}
