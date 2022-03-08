#pragma once

#include <SFML/Graphics.hpp>


class LevelManager
{
private:
    sf::Vector2i m_LevelSize;
    sf::Vector2f m_StartPosition;
    float m_TimeModifier = 1.0f;
    float m_BaseTimeLimit = 0.0f;
    int m_CurrentLevel = 0;
    const int NUM_LEVELS = 4;

public:
    const int TILE_SIZE = 50;
    const int VERTS_IN_QUAD = 4;

    float getTimeLimit();
    int getCurrentLevel();

    sf::Vector2f getStartPosition();
    sf::Vector2i getLevelSize();

    int** nextLevel(sf::VertexArray& rVaLevel);
};
