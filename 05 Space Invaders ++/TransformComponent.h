#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Component.h"


class Component;

class TransformComponent : public Component
{
private:
    const std::string m_Type = "transform";
    sf::Vector2f m_Location;
    float m_Height;
    float m_Width;

public:
    TransformComponent(float width, float height, sf::Vector2f location);
    sf::Vector2f& getLocation();
    sf::Vector2f getSize();

    std::string Component::getType()
    {
        return m_Type;
    }

    std::string Component::getSpecificType()
    {
        return m_Type;
    }

    void Component::disableComponent() {}
    void Component::enableComponent() {}
    bool Component::enabled()
    {
        return false;
    }
    void Component::start(GameObjectSharer* gos, GameObject* self) {}
};
