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

    sf::Vector2f& getLocation();
};
