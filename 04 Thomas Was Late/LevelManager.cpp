#include <fstream>
#include <sstream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "LevelManager.h"
#include "TextureHolder.h"


int** LevelManager::nextLevel(sf::VertexArray& rVaLevel)
{
    m_LevelSize.x = 0;
    m_LevelSize.y = 0;
    m_CurrentLevel++;

    if (m_CurrentLevel > NUM_LEVELS) {
        m_CurrentLevel = 1;
        m_TimeModifier -= 0.1f;
    }

    std::string levelToLoad;
    switch (m_CurrentLevel) {
        case 1:
            levelToLoad = "levels/level1.txt";
            m_StartPosition.x = 100;
            m_StartPosition.y = 100;
            m_BaseTimeLimit = 30.0f;
            break;
        case 2:
            levelToLoad = "levels/level2.txt";
            m_StartPosition.x = 100;
            m_StartPosition.y = 3600;
            m_BaseTimeLimit = 100.0f;
            break;
        case 3:
            levelToLoad = "levels/level3.txt";
            m_StartPosition.x = 1250;
            m_StartPosition.y = 0;
            m_BaseTimeLimit = 30.0f;
            break;
        case 4:
            levelToLoad = "levels/level4.txt";
            m_StartPosition.x = 50;
            m_StartPosition.y = 200;
            m_BaseTimeLimit = 50.0f;
            break;
    }

    std::ifstream inputFile(levelToLoad);
    std::string s;

    while (std::getline(inputFile, s)) {
        ++m_LevelSize.y;
    }
    m_LevelSize.x = s.length();

    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    int** arrayLevel = new int* [m_LevelSize.y];
    for (int i = 0; i < m_LevelSize.y; ++i) {
        arrayLevel[i] = new int[m_LevelSize.x];
    }

    std::string row;
    int y = 0;
    while (inputFile >> row) {
        for (int x = 0; x < (int)row.length(); x++) {
            const char val = row[x];
            arrayLevel[y][x] = atoi(&val);
        }
        y++;
    }
    inputFile.close();

    rVaLevel.setPrimitiveType(sf::Quads);
    rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);
    int currentVertex = 0;
    for (int x = 0; x < m_LevelSize.x; x++) {
        for (int y = 0; y < m_LevelSize.y; y++) {
            rVaLevel[currentVertex + 0].position = sf::Vector2f(x * TILE_SIZE * 1.0f, y * TILE_SIZE * 1.0f);
            rVaLevel[currentVertex + 1].position = sf::Vector2f((x + 1) * TILE_SIZE * 1.0f, y * TILE_SIZE * 1.0f);
            rVaLevel[currentVertex + 2].position = sf::Vector2f((x + 1) * TILE_SIZE * 1.0f, (y + 1) * TILE_SIZE * 1.0f);
            rVaLevel[currentVertex + 3].position = sf::Vector2f(x * TILE_SIZE * 1.0f, (y + 1) * TILE_SIZE * 1.0f);

            float verticalOffset = arrayLevel[y][x] * TILE_SIZE * 1.0f;
            rVaLevel[currentVertex + 0].texCoords = sf::Vector2f(0, 0 + verticalOffset);
            rVaLevel[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE * 1.0f, 0 + verticalOffset);
            rVaLevel[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE * 1.0f, TILE_SIZE + verticalOffset);
            rVaLevel[currentVertex + 3].texCoords = sf::Vector2f(0, TILE_SIZE + verticalOffset);

            currentVertex += VERTS_IN_QUAD;
        }
    }
    return arrayLevel;
}

sf::Vector2i LevelManager::getLevelSize()
{
    return m_LevelSize;
}

int LevelManager::getCurrentLevel()
{
    return m_CurrentLevel;
}

float LevelManager::getTimeLimit()
{
    return m_BaseTimeLimit * m_TimeModifier;
}

sf::Vector2f LevelManager::getStartPosition()
{
    return m_StartPosition;
}
