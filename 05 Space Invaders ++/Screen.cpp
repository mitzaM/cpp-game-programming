#include <memory>
#include <utility>
#include <vector>

#include "Screen.h"


void Screen::initialise() {}

void Screen::addPanel(std::unique_ptr<UIPanel> uip, ScreenManagerRemoteControl* smrc, std::shared_ptr<InputHandler> ih)
{
    ih->initialiseInputHandler(smrc, uip->getButtons(), &uip->m_View, this);
    m_Panels.push_back(std::move(uip));
    m_InputHandlers.push_back(ih);
}

void Screen::handleInput(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        for (std::vector<std::shared_ptr<InputHandler>>::iterator i = m_InputHandlers.begin(); i != m_InputHandlers.end(); ++i) {
            (*i)->handleInput(window, event);
        }
    }
}

void Screen::update(float fps) {}

void Screen::draw(sf::RenderWindow& window)
{
    for (std::vector<std::unique_ptr<UIPanel>>::iterator i = m_Panels.begin(); i != m_Panels.end(); ++i) {
        (*i)->draw(window);
    }
}
