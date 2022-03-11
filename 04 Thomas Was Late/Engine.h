#pragma once

#include <SFML/Graphics.hpp>

#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "TextureHolder.h"
#include "Thomas.h"


class Engine
{
private:
    TextureHolder th;
    Thomas m_Thomas;
    Bob m_Bob;
    LevelManager m_LM;
    SoundManager m_SM;

    const int TILE_SIZE = 50;
    const int VERTS_IN_QUAD = 4;

    const int GRAVITY = 300;

    sf::RenderWindow m_Window;

    sf::View m_MainView;
    sf::View m_LeftView;
    sf::View m_RightView;

    sf::View m_BGMainView;
    sf::View m_BGLeftView;
    sf::View m_BGRightView;

    sf::View m_HudView;

    sf::Sprite m_BackgroundSprite;
    sf::Texture m_BackgroundTexture;

    bool m_Playing = false;
    bool m_Character1 = true;
    bool m_SplitScreen = false;

    float m_TimeRemaining = 10.0f;
    sf::Time m_GameTimeTotal = sf::seconds(0);

    bool m_NewLevelRequired = true;

    sf::VertexArray m_VALevel;
    int** m_ArrayLevel = NULL;
    sf::Texture m_TextureTiles;

    void input();
    void update(float dtAsSeconds);
    void draw();

    void loadLevel();
    bool detectCollisions(PlayableCharacter& character);

    void populateEmitters(std::vector <sf::Vector2f>& vSoundEmitters, int** arrayLevel);
    std::vector <sf::Vector2f> m_FireEmitters;

public:
    Engine();
    void run();
};
