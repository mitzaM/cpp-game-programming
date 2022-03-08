#include "Engine.h"


bool Engine::detectCollisions(PlayableCharacter& character)
{
    bool reachedGoal = false;

    sf::FloatRect detectionZone = character.getPosition();
    sf::FloatRect block;
    block.width = TILE_SIZE * 1.0f;
    block.height = TILE_SIZE * 1.0f;

    int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
    int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
    int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
    int endY = (int)(detectionZone.top / TILE_SIZE) + 3;
    int levelX = m_LM.getLevelSize().x;
    int levelY = m_LM.getLevelSize().y;

    if (startX < 0) {
        startX = 0;
    }
    if (startY < 0) {
        startY = 0;
    }
    if (endX >= levelX) {
        endX = levelX;
    }
    if (endY >= levelY) {
        endY = levelY;
    }

    sf::FloatRect level(0, 0, levelX * TILE_SIZE * 1.0f, levelY * TILE_SIZE * 1.0f);
    if (!character.getPosition().intersects(level)) {
        character.spawn(m_LM.getStartPosition(), GRAVITY * 1.0f);
    }

    for (int x = startX; x < endX; x++) {
        for (int y = startY; y < endY; y++) {
            block.left = x * TILE_SIZE * 1.0f;
            block.top = y * TILE_SIZE * 1.0f;

            if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3) {
                if (character.getHead().intersects(block)) {
                    character.spawn(m_LM.getStartPosition(), GRAVITY * 1.0f);
                    if (m_ArrayLevel[y][x] == 2) {
                        // fire sound
                    } else {
                        // water sound
                    }
                }
            }
            if (m_ArrayLevel[y][x] == 1) {
                if (character.getRight().intersects(block)) {
                    character.stopRight(block.left);
                } else if (character.getLeft().intersects(block)) {
                    character.stopLeft(block.left);
                } else if (character.getFeet().intersects(block)) {
                    character.stopFalling(block.top);
                } else if (character.getHead().intersects(block)) {
                    character.stopJump();
                }
            }
            if (m_ArrayLevel[y][x] == 4) {
                reachedGoal = true;
            }
        }
    }

    return reachedGoal;
}
