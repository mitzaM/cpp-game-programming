#include <string>

#include "Button.h"


Button::Button(sf::Vector2f position, float width, float height, int red, int green, int blue, std::string text)
{
    m_Button.setPosition(position);
    m_Button.setFillColor(sf::Color(red, green, blue));
    m_Button.setSize(sf::Vector2f(width, height));

    m_Text = "" + text;
    m_Font.loadFromFile("fonts/Roboto-Bold.ttf");

    m_ButtonText.setFont(m_Font);
    m_ButtonText.setCharacterSize(static_cast<unsigned int>(height * 0.7f));
    m_ButtonText.setString(m_Text);
    m_ButtonText.setPosition(sf::Vector2f(position.x + width / 10, position.y + height / 10));

    m_Collider = sf::FloatRect(position, sf::Vector2f(width, height));
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(m_Button);
    window.draw(m_ButtonText);
}
