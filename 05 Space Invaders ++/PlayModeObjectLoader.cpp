#include <fstream>
#include <string>
#include <vector>

#include "GameObject.h"
#include "ObjectTags.h"
#include "PlayModeObjectLoader.h"


void PlayModeObjectLoader::loadGameObjectsForPlayMode(std::string pathToFile, std::vector<GameObject>& gameObjects)
{
    std::ifstream reader(pathToFile);
    std::string lineFromFile;

    float x = 0.0f, y = 0.0f, width = 0.0f, height = 0.0f;
    std::string value = "";

    while (std::getline(reader, lineFromFile)) {
        if (lineFromFile.find(ObjectTags::START_OF_OBJECT) != std::string::npos) {
            GameObjectBlueprint bp;
            m_BOP.parseNextObjectForBlueprint(reader, bp);
            m_GameObjectFactoryPlayMode.buildGameObject(bp, gameObjects);
        }
    }
}
