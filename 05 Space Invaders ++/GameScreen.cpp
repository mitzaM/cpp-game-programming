#include <memory>
#include <utility>

#include "GameInputHandler.h"
#include "GameOverInputHandler.h"
#include "GameScreen.h"
#include "GameOverUIPanel.h"
#include "GameUIPanel.h"
#include "WorldState.h"


int WorldState::NUM_INVADERS;
int WorldState::NUM_INVADERS_AT_START;
int WorldState::WORLD_HEIGHT;

GameScreen::GameScreen(ScreenManagerRemoteControl* smrc, sf::Vector2i res)
{
    m_GIH = std::make_shared<GameInputHandler>();
    auto guip = std::make_unique<GameUIPanel>(res);
    addPanel(std::move(guip), smrc, m_GIH);

    auto m_GOIH = std::make_shared<GameOverInputHandler>();
    auto gouip = std::make_unique<GameOverUIPanel>(res);
    addPanel(std::move(gouip), smrc, m_GOIH);

    m_ScreenManagerRemoteControl = smrc;
    float screenRatio = float(sf::VideoMode::getDesktopMode().width / sf::VideoMode::getDesktopMode().height);
    WorldState::WORLD_HEIGHT = int(WorldState::WORLD_WIDTH / screenRatio);
    m_View.setSize(WorldState::WORLD_WIDTH * 1.0f, WorldState::WORLD_HEIGHT * 1.0f);
    m_View.setCenter(
        sf::Vector2f(WorldState::WORLD_WIDTH / 2.0f, WorldState::WORLD_HEIGHT / 2.0f)
    );

    m_BackgroundTexture.loadFromFile("graphics/background.png");
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
    auto textureSize = m_BackgroundSprite.getTexture()->getSize();
    m_BackgroundSprite.setScale(
        float(m_View.getSize().x) / textureSize.x,
        float(m_View.getSize().y) / textureSize.y
    );
}

void GameScreen::initialise()
{
    m_GIH->initialise();
    WorldState::NUM_INVADERS = 0;
    m_GameOver = false;

    if (WorldState::WAVE_NUMBER == 0) {
        WorldState::NUM_INVADERS_AT_START = WorldState::NUM_INVADERS;
        WorldState::WAVE_NUMBER = 1;
        WorldState::LIVES = 3;
        WorldState::SCORE = 0;
    }
}

void GameScreen::update(float fps)
{
    Screen::update(fps);
    if (!m_GameOver) {
        if (WorldState::NUM_INVADERS <= 0) {
            WorldState::WAVE_NUMBER++;
            m_ScreenManagerRemoteControl->loadLevelInPlayMode("level1");
        }
        if (WorldState::LIVES <= 0) {
            m_GameOver = true;
        }
    }
}

void GameScreen::draw(sf::RenderWindow& window)
{
    window.setView(m_View);
    window.draw(m_BackgroundSprite);
    Screen::draw(window);
}

BulletSpawner* GameScreen::getBulletSpawner()
{
    return this;
}
