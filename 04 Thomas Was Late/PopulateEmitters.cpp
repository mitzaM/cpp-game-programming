#include "Engine.h"


void Engine::populateEmitters(std::vector <sf::Vector2f>& vSoundEmitters, int** arrayLevel)
{
    vSoundEmitters.clear();
    sf::FloatRect previousEmitter;

    for (int x = 0; x < (int)m_LM.getLevelSize().x; x++) {
        for (int y = 0; y < (int)m_LM.getLevelSize().y; y++) {
            if (arrayLevel[y][x] == 2) {
                sf::FloatRect currentBlock = sf::FloatRect(
                    x * TILE_SIZE * 1.0f, y * TILE_SIZE * 1.0f, TILE_SIZE * 1.0f, TILE_SIZE * 1.0f
                );
                if (!currentBlock.intersects(previousEmitter)) {
                    vSoundEmitters.push_back(sf::Vector2f(
                        currentBlock.left, currentBlock.top
                    ));
                    previousEmitter.left = currentBlock.left;
                    previousEmitter.top = currentBlock.top;
                    previousEmitter.width = TILE_SIZE * 6.0f;
                    previousEmitter.height = TILE_SIZE * 6.0f;
                }
            }
        }
    }
    return;
}
