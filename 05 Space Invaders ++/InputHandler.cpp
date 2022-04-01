#include <memory>
#include <string>
#include <vector>

#include "InputHandler.h"


void InputHandler::initialiseInputHandler(ScreenManagerRemoteControl* sw, std::vector<std::shared_ptr<Button>> buttons, sf::View* pointerToUIView, Screen* parentScreen)
{
    m_ScreenManagerRemoteControl = sw;
    m_Buttons = buttons;
    m_PointerToUIPanelView = pointerToUIView;
    m_ParentScreen = parentScreen;
}

void InputHandler::handleInput(sf::RenderWindow& window, sf::Event& event)
{
    switch (event.type) {
        case sf::Event::KeyPressed:
            handleKeyPressed(event, window);
            break;
        case sf::Event::KeyReleased:
            handleKeyReleased(event, window);
            break;
        case sf::Event::MouseButtonReleased:
            for (std::vector<std::shared_ptr<Button>>::iterator i = m_Buttons.begin(); i != m_Buttons.end(); ++i) {
                if ((*i)->m_Collider.contains(window.mapPixelToCoords(sf::Mouse::getPosition(), *getPointerToUIView()))) {
                    handleLeftClick((*i)->m_Text, window);
                    break;
                }
            }
            break;
    }
    handleGamepad();
}

void InputHandler::handleGamepad() {}

void InputHandler::handleKeyPressed(sf::Event& event, sf::RenderWindow& window) {}

void InputHandler::handleKeyReleased(sf::Event& event, sf::RenderWindow& window) {}

void InputHandler::handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window) {}

sf::View* InputHandler::getPointerToUIView()
{
    return m_PointerToUIPanelView;
}

ScreenManagerRemoteControl* InputHandler::getPointerToScreenManagerRemoteControl()
{
    return m_ScreenManagerRemoteControl;
}

Screen* InputHandler::getParentScreen()
{
    return m_ParentScreen;
}
