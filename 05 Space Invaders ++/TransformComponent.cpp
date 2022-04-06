#include "TransformComponent.h"


TransformComponent::TransformComponent(float width, float height, sf::Vector2f location)
{
    m_Height = height;
    m_Width = width;
    m_Location = location;
}

sf::Vector2f& TransformComponent::getLocation()
{
    return m_Location;
}

sf::Vector2f TransformComponent::getSize()
{
    return sf::Vector2f(m_Width, m_Height);
}
