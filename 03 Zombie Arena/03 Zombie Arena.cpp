#include <SFML/Graphics.hpp>

#include "Player.h"
#include "TextureHolder.h"
#include "ZombieArena.h"

int main()
{
    TextureHolder holder;

    enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
    State state = State::GAME_OVER;

    sf::Vector2u resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Zombie Arena", sf::Style::Fullscreen);
    sf::View mainView(sf::FloatRect(0, 0, (float)resolution.x, (float)resolution.y));

    sf::Clock clock;
    sf::Time gameTimeTotal;

    sf::Vector2f mouseWorldPosition;
    sf::Vector2i mouseScreenPosition;

    Player player;
    sf::IntRect arena;

    sf::VertexArray background;
    sf::Texture textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

    int numZombies;
    int numZombiesAlive;
    Zombie* zombies = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    switch (state) {
                    case State::PLAYING:
                        state = State::PAUSED;
                        break;
                    case State::PAUSED:
                        state = State::PLAYING;
                        clock.restart();
                        break;
                    case State::GAME_OVER:
                        state = State::LEVELING_UP;
                        break;
                    }
                }
                if (state == State::PLAYING) {

                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        if (state == State::PLAYING) {
            sf::Keyboard::isKeyPressed(sf::Keyboard::W) ? player.moveUp() : player.stopUp();
            sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? player.moveDown() : player.stopDown();
            sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? player.moveLeft() : player.stopLeft();
            sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? player.moveRight() : player.stopRight();
        }

        if (state == State::LEVELING_UP) {
            switch (event.key.code) {
            case sf::Keyboard::Num1:
                state = State::PLAYING;
                break;
            case sf::Keyboard::Num2:
                state = State::PLAYING;
                break;
            case sf::Keyboard::Num3:
                state = State::PLAYING;
                break;
            case sf::Keyboard::Num4:
                state = State::PLAYING;
                break;
            case sf::Keyboard::Num5:
                state = State::PLAYING;
                break;
            case sf::Keyboard::Num6:
                state = State::PLAYING;
                break;
            }

            if (state == State::PLAYING) {
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                int tileSize = createBackground(background, arena);
                player.spawn(arena, resolution, tileSize);

                numZombies = 10;
                delete[] zombies;
                zombies = createHorde(numZombies, arena);
                numZombiesAlive = numZombies;

                clock.restart();
            }
        }

        if (state == State::PLAYING) {
            sf::Time dt = clock.restart();
            gameTimeTotal += dt;

            mouseScreenPosition = sf::Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);

            player.update(dt.asSeconds(), sf::Mouse::getPosition());
            sf::Vector2f playerPosition(player.getCenter());
            mainView.setCenter(player.getCenter());

            for (int i = 0; i < numZombies; i++) {
                if (zombies[i].isAlive()) {
                    zombies[i].update(dt.asSeconds(), playerPosition);
                }
            }
        }

        if (state == State::PLAYING) {
            window.clear();
            window.setView(mainView);
            window.draw(background, &textureBackground);
            for (int i = 0; i < numZombies; i++) {
                window.draw(zombies[i].getSprite());
            }
            window.draw(player.getSprite());
        }
        if (state == State::LEVELING_UP) {

        }
        if (state == State::PAUSED) {

        }
        if (state == State::GAME_OVER) {

        }
        window.display();
    }

    delete[] zombies;
    return 0;
}
