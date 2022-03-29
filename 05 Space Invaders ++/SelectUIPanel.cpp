#include "SelectUIPanel.h"


SelectUIPanel::SelectUIPanel(sf::Vector2i res) : UIPanel(res, (res.x / 10) * 2, res.y / 3, (res.x / 10) * 6.0f, res.y / 3.0f, 50, 255, 255, 255)
{
    m_ButtonWidth = res.x / 20.0f;
    m_ButtonHeight = res.y / 20.0f;
    m_ButtonPadding = res.x / 100.0f;

    m_Text.setFillColor(sf::Color(0, 255, 0, 255));
    m_Text.setString("SPACE INVADERS ++");

    m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
    m_Text.setFont(m_Font);

    m_Text.setPosition(sf::Vector2f(
        m_ButtonPadding,
        m_ButtonHeight + m_ButtonPadding * 2
    ));
    m_Text.setCharacterSize(160);

    initialiseButtons();
}

void SelectUIPanel::initialiseButtons()
{
    addButton(m_ButtonPadding, m_ButtonPadding, (int)m_ButtonWidth, (int)m_ButtonHeight, 0, 255, 0, "Play");
    addButton(m_ButtonWidth + m_ButtonPadding * 2, m_ButtonPadding, (int)m_ButtonWidth, (int)m_ButtonHeight, 255, 0, 0, "Quit");
}

void SelectUIPanel::draw(sf::RenderWindow& window)
{
    show();
    UIPanel::draw(window);
    window.draw(m_Text);
}
