#include <memory>

#include "GameEngine.h"


GameEngine::GameEngine()
{
    m_Resolution.x = sf::VideoMode::getDesktopMode().width;
    m_Resolution.y = sf::VideoMode::getDesktopMode().height;
    m_Window.create(sf::VideoMode(m_Resolution.x, m_Resolution.y), "Space Invaders++", sf::Style::Fullscreen);
    m_ScreenManager = std::unique_ptr<ScreenManager>(new ScreenManager(sf::Vector2i((int)m_Resolution.x, (int)m_Resolution.y)));
}

void GameEngine::run()
{
    while (m_Window.isOpen()) {
        m_DT = m_Clock.restart();
        m_FPS = m_DT.asSeconds();
        handleInput();
        update();
        draw();
    }
}

void GameEngine::handleInput()
{
    m_ScreenManager->handleInput(m_Window);
}

void GameEngine::update()
{
    m_ScreenManager->update(m_FPS);
}

void GameEngine::draw()
{
    m_Window.clear(sf::Color::Black);
    m_ScreenManager->draw(m_Window);
    m_Window.display();
}
