#include "Engine.h"


void Engine::input()
{
    sf::Event event;
    while (m_Window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                m_Window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                m_Playing = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                m_Character1 = !m_Character1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                m_SplitScreen = !m_SplitScreen;
            }
        }
    }
    if (m_Thomas.handleInput()) {
        m_SM.playJump();
    }
    if (m_Bob.handleInput()) {
        m_SM.playJump();
    }
}
