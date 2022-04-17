#pragma once

#include <string>
#include <vector>

#include "BlueprintObjectParser.h"
#include "GameObject.h"
#include "GameObjectFactoryPlayMode.h"


class PlayModeObjectLoader
{
private:
    BlueprintObjectParser m_BOP;
    GameObjectFactoryPlayMode m_GameObjectFactoryPlayMode;

public:
    void loadGameObjectsForPlayMode(std::string pathToFile, std::vector<GameObject>& mGameObjects);
};
