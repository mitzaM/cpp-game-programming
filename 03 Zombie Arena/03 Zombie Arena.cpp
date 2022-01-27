#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

int main()
{
    enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
    State state = State::GAME_OVER;

    Vector2u resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);
    View mainView(sf::FloatRect(0, 0, (float)resolution.x, (float)resolution.y));

    Clock clock;
    Time gameTimeTotal;

    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;

    Player player;
    IntRect arena;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return) {
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

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (state == State::PLAYING) {
            Keyboard::isKeyPressed(Keyboard::W) ? player.moveUp() : player.stopUp();
            Keyboard::isKeyPressed(Keyboard::S) ? player.moveDown() : player.stopDown();
            Keyboard::isKeyPressed(Keyboard::A) ? player.moveLeft() : player.stopLeft();
            Keyboard::isKeyPressed(Keyboard::D) ? player.moveRight() : player.stopRight();
        }

        if (state == State::LEVELING_UP) {
            switch (event.key.code) {
            case Keyboard::Num1:
                state = State::PLAYING;
                break;
            case Keyboard::Num2:
                state = State::PLAYING;
                break;
            case Keyboard::Num3:
                state = State::PLAYING;
                break;
            case Keyboard::Num4:
                state = State::PLAYING;
                break;
            case Keyboard::Num5:
                state = State::PLAYING;
                break;
            case Keyboard::Num6:
                state = State::PLAYING;
                break;
            }

            if (state == State::PLAYING) {
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;
                int tileSize = 50;
                player.spawn(arena, resolution, tileSize);
                clock.restart();
            }
        }

        if (state == State::PLAYING) {
            Time dt = clock.restart();
            gameTimeTotal += dt;
            float dtAsSeconds = dt.asSeconds();
            mouseScreenPosition = Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);
            player.update(dtAsSeconds, Mouse::getPosition());
            Vector2f playerPosition(player.getCenter());
            mainView.setCenter(player.getCenter());
        }

        if (state == State::PLAYING) {
            window.clear();
            window.setView(mainView);
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

    return 0;
}
