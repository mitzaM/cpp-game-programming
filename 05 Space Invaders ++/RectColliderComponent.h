#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "ColliderComponent.h"


class RectColliderComponent : public ColliderComponent
{
private:
    std::string m_SpecificType = "rect";
    sf::FloatRect m_Collider;
    std::string m_Tag = "";

public:
    RectColliderComponent(std::string name);
    std::string getColliderTag();
    void setOrMoveCollider(float x, float y, float width, float height);
    sf::FloatRect& getColliderRectF();

    std::string getSpecificType()
    {
        return m_SpecificType;
    }

    void Component::start(GameObjectSharer* gos, GameObject* self) {};
};
