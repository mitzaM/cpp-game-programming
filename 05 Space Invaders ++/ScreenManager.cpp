#include "ScreenManager.h"


ScreenManager::ScreenManager(sf::Vector2i res)
{
    m_Screens["Game"] = std::unique_ptr<GameScreen>(new GameScreen(this, res));
    m_Screens["Select"] = std::unique_ptr<SelectScreen>(new SelectScreen(this, res));
}

void ScreenManager::handleInput(sf::RenderWindow& window)
{
    m_Screens[m_CurrentScreen]->handleInput(window);
}

void ScreenManager::update(float fps)
{
    m_Screens[m_CurrentScreen]->update(fps);
}

void ScreenManager::draw(sf::RenderWindow& window)
{
    m_Screens[m_CurrentScreen]->draw(window);
}
