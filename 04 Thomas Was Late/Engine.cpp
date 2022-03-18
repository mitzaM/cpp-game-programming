#include "Engine.h"


Engine::Engine()
{
    unsigned int x = sf::VideoMode::getDesktopMode().width;
    unsigned int y = sf::VideoMode::getDesktopMode().height;
    sf::Vector2f resolution((float)x, (float)y);

    m_Window.create(sf::VideoMode(x, y), "Thomas Was Late", sf::Style::Fullscreen);

    m_MainView.setSize(resolution);
    m_HudView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));

    sf::FloatRect leftSide(0.001f, 0.001f, 0.498f, 0.998f);
    m_LeftView.setViewport(leftSide);
    m_BGLeftView.setViewport(leftSide);

    sf::FloatRect rightSide(0.5f, 0.001f, 0.499f, 0.998f);
    m_RightView.setViewport(rightSide);
    m_BGRightView.setViewport(rightSide);

    m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");
    m_BackgroundSprite.setTexture(m_BackgroundTexture);

    m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");
    m_PS.init(1000);
}

void Engine::run()
{
    sf::Clock clock;

    while (m_Window.isOpen()) {
        sf::Time dt = clock.restart();
        m_GameTimeTotal += dt;
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}
