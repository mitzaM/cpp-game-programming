#include "UIPanel.h"


UIPanel::UIPanel(sf::Vector2i res, int x, int y, float width, float height, int alpha, int red, int green, int blue)
{
    m_UIPanel.setFillColor(sf::Color(red, green, blue, alpha));
    m_UIPanel.setSize(sf::Vector2f(width, height));

    m_View.setSize(sf::Vector2f(width, height));
    m_View.setCenter(width / 2, height / 2);

    float viewportStartX = 1.0f / (res.x / x);
    float viewportStartY = 1.0f / (res.y / y);
    float viewportSizeX = 1.0f / (res.x / width);
    float viewportSizeY = 1.0f / (res.y / height);
    m_View.setViewport(sf::FloatRect(
        viewportStartX, viewportStartY, viewportSizeX, viewportSizeY
    ));
}

std::vector<std::shared_ptr<Button>> UIPanel::getButtons()
{
    return m_Buttons;
}

void UIPanel::addButton(float x, float y, int width, int height, int red, int green, int blue, std::string label)
{
    m_Buttons.push_back(std::make_shared<Button>(
        sf::Vector2f(x, y), width * 1.0f, height * 1.0f, red, green, blue, label)
    );
}

void UIPanel::draw(sf::RenderWindow& window)
{
    window.setView(m_View);
    if (!m_Hidden) {
        window.draw(m_UIPanel);
        for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it) {
            (*it)->draw(window);
        }
    }
}

void UIPanel::show()
{
    m_Hidden = false;
}

void UIPanel::hide()
{
    m_Hidden = true;
}
