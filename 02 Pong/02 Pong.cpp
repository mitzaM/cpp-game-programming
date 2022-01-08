#include "Ball.h"
#include "Bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main()
{
    VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);
    RenderWindow window(vm, "Pong", Style::Fullscreen);

    int score = 0;
    int lives = 3;

    Ball ball(SCREEN_WIDTH / 2, 0);
    Bat bat(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 20);

    Font font;
    font.loadFromFile("fonts/DS-DIGIT.ttf");

    Text hud;
    hud.setFont(font);
    hud.setCharacterSize(75);
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);

    Clock clock;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            bat.moveLeft();
        }
        else {
            bat.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            bat.moveRight();
        }
        else {
            bat.stopRight();
        }

        Time dt = clock.restart();
        ball.update(dt);
        bat.update(dt);
        std::stringstream ss;
        ss << "Score:" << score << "  Lives:" << lives;
        hud.setString(ss.str());

        window.clear();
        window.draw(hud);
        window.draw(ball.getShape());
        window.draw(bat.getShape());
        window.display();
    }

    return 0;
}
