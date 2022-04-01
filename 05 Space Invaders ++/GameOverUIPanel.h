#pragma once

#include "UIPanel.h"


class GameOverUIPanel : public UIPanel
{
private:
    void initialiseButtons();

public:
    GameOverUIPanel(sf::Vector2i res);
    void virtual draw(sf::RenderWindow& window);
};
