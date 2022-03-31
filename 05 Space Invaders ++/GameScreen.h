#pragma once

#include <memory>

#include "GameInputHandler.h"
#include "GameOverInputHandler.h"
#include "Screen.h"


class GameScreen : public Screen
{
private:
    ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
    std::shared_ptr<GameInputHandler> m_GIH;

    sf::Texture m_BackgroundTexture;
    sf::Sprite m_BackgroundSprite;

public:
    static bool m_GameOver;

    GameScreen(ScreenManagerRemoteControl* smrc, sf::Vector2i res);
    void initialise() override;
    void virtual update(float fps);
    void virtual draw(sf::RenderWindow& window);
};
