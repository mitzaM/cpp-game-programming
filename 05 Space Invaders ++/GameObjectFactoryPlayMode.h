#pragma once

#include <vector>

#include "GameObject.h"
#include "GameObjectBlueprint.h"


class GameObjectFactoryPlayMode
{
public:
    void buildGameObject(GameObjectBlueprint& bp, std::vector<GameObject>& gameObjects);
};
