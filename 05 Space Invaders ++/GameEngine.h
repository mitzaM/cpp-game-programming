#pragma once

#include <SFML/Graphics.hpp>

#include "ScreenManager.h"
#include "SoundEngine.h"


class GameEngine
{
private:
    sf::Clock m_Clock;
    sf::Time m_DT;
    sf::RenderWindow m_Window;

    std::unique_ptr<ScreenManager> m_ScreenManager;

    float m_FPS = 0;
    sf::Vector2f m_Resolution;

    void handleInput();
    void update();
    void draw();

public:
    SoundEngine m_SoundEngine;

    GameEngine();
    void run();
};
