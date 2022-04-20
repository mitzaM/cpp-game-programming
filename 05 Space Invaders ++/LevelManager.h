#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "GameObject.h"
#include "GameObjectSharer.h"


class LevelManager : public GameObjectSharer
{
private:
    std::vector<GameObject> m_GameObjects;

    const std::string WORLD_FOLDER = "world";
    const std::string SLASH = "/";

    void runStartPhase();
    void activateAllGameObjects();

public:
    std::vector<GameObject>& getGameObjects();
    void loadGameObjectsForPlayMode(std::string screenToLoad);

    std::vector<GameObject>& GameObjectSharer::getGameObjectsWithGOS()
    {
        return m_GameObjects;
    }

    GameObject& GameObjectSharer::findFirstObjectWithTag(std::string tag)
    {
        for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it) {
            if ((*it).getTag() == tag) {
                return (*it);
            }
        }

        #ifdef debuggingOnConsole
        std::cout << "LevelManager.h::findFirstObjectWithTag - TAG NOT FOUND ERROR!" << std::endl;
        #endif // debuggingOnConsole
        return m_GameObjects[0];
    }
};
