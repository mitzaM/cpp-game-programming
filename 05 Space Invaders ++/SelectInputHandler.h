#pragma once

#include <string>

#include "InputHandler.h"


class SelectInputHandler : public InputHandler
{
    void handleKeyPressed(sf::Event& event, sf::RenderWindow& window) override;
    void handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window) override;
};
