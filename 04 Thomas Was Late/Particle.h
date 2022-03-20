#pragma once

#include <SFML/Graphics.hpp>


class Particle
{
private:
    sf::Vector2f m_Position;
    sf::Vector2f m_Velocity;

public:
    Particle(sf::Vector2f direction);

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);

    void update(float dt);
};
