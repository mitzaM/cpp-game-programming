#include <string>
#include <vector>

#include "LevelManager.h"
#include "PlayModeObjectLoader.h"


void LevelManager::loadGameObjectsForPlayMode(std::string screenToLoad)
{
    m_GameObjects.clear();
    std::string levelToLoad = "" + WORLD_FOLDER + SLASH + screenToLoad;

    PlayModeObjectLoader pmol;
    pmol.loadGameObjectsForPlayMode(levelToLoad, m_GameObjects);
    runStartPhase();
}

std::vector<GameObject>& LevelManager::getGameObjects()
{
    return m_GameObjects;
}

void LevelManager::runStartPhase()
{
    for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it) {
        (*it).start(this);
    }
    activateAllGameObjects();
}

void LevelManager::activateAllGameObjects()
{
    for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it) {
        (*it).setActive();
    }
}
