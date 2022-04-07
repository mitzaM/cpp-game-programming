#include <string>

#include "RectColliderComponent.h"


RectColliderComponent::RectColliderComponent(std::string name)
{
    m_Tag = "" + name;
}

std::string RectColliderComponent::getColliderTag()
{
    return m_Tag;
}

void RectColliderComponent::setOrMoveCollider(float x, float y, float width, float height)
{
    m_Collider.left = x;
    m_Collider.top = y;
    m_Collider.width = width;
    m_Collider.height = height;
}

sf::FloatRect& RectColliderComponent::getColliderRectF()
{
    return m_Collider;
}
