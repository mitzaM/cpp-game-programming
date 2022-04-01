#pragma once

#include "InputHandler.h"


class GameScreen;

class GameInputHandler : public InputHandler
{
public:
    void initialise();
    void handleGamepad() override;
    void handleKeyPressed(sf::Event& event, sf::RenderWindow& window) override;
    void handleKeyReleased(sf::Event& event, sf::RenderWindow& window) override;
};
