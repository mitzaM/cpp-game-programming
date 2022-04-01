#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BitmapStore.h"
#include "GameScreen.h"
// #include "LevelManager.h"
#include "Screen.h"
#include "ScreenManagerRemoteControl.h"
#include "SelectScreen.h"


class ScreenManager : public ScreenManagerRemoteControl
{
private:
    std::map<std::string, std::unique_ptr<Screen>> m_Screens;
    // LevelManager m_LevelManager;

protected:
    std::string m_CurrentScreen = "Select";

public:
    ScreenManager(sf::Vector2i res);

    void update(float fps);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window);

    BitmapStore m_BS;

    void ScreenManagerRemoteControl::SwitchScreens(std::string screenToSwitchTo)
    {
        m_CurrentScreen = "" + screenToSwitchTo;
        m_Screens[m_CurrentScreen]->initialise();
    }

    void ScreenManagerRemoteControl::loadLevelInPlayMode(std::string screenToLoad)
    {
        // m_LevelManager.getGameObjects().clear();
        // m_LevelManager.loadGameObjectsForPlayMode(screenToLoad);
        SwitchScreens("Game");
    }

    // std::vector<GameObject>& ScreenManagerRemoteControl::getGameObjects()
    // {
    //     return m_LevelManager.getGameObjects();
    // }

    // GameObjectSharer& shareGameObjectSharer()
    // {
    //     return m_LevelManager;
    // }
};
