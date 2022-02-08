#include <SFML/Graphics.hpp>

#include "Bullet.h"
#include "Pickup.h"
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

    const int NUM_BULLETS = 100;
    Bullet bullets[NUM_BULLETS];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1.0f;
    sf::Time lastPressed;

    window.setMouseCursorVisible(true);
    sf::Sprite spriteCrosshair = sf::Sprite(TextureHolder::GetTexture("graphics/crosshair.png"));
    spriteCrosshair.setOrigin(25, 25);

    Pickup healthPickup(PickupType::HEALTH);
    Pickup ammoPickup(PickupType::AMMO);

    int score = 0;
    int hiScore = 0;

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
                    if (event.key.code == sf::Keyboard::R) {
                        if (bulletsSpare >= clipSize) {
                            bulletsInClip = clipSize;
                            bulletsSpare -= clipSize;
                        }
                        else if (bulletsSpare > 0) {
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                        }
                        else {

                        }
                    }
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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0) {
                    bullets[currentBullet].shoot(
                        player.getCenter().x, player.getCenter().y,
                        mouseWorldPosition.x, mouseWorldPosition.y
                    );
                    currentBullet++;
                    if (currentBullet > 99) {
                        currentBullet = 0;
                    }
                    lastPressed = gameTimeTotal;
                    bulletsInClip--;
                }
            }
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

                healthPickup.setArena(arena);
                ammoPickup.setArena(arena);

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
            spriteCrosshair.setPosition(mouseWorldPosition);

            player.update(dt.asSeconds(), sf::Mouse::getPosition());
            sf::Vector2f playerPosition(player.getCenter());
            mainView.setCenter(player.getCenter());

            for (int i = 0; i < numZombies; i++) {
                if (zombies[i].isAlive()) {
                    zombies[i].update(dt.asSeconds(), playerPosition);
                }
            }
            for (int i = 0; i < NUM_BULLETS; i++) {
                if (bullets[i].isInFlight()) {
                    bullets[i].update(dt.asSeconds());
                }
            }

            healthPickup.update(dt.asSeconds());
            ammoPickup.update(dt.asSeconds());

            for (int i = 0; i < NUM_BULLETS; i++) {
                for (int j = 0; j < numZombies; j++) {
                    if (bullets[i].isInFlight() && zombies[j].isAlive()) {
                        if (bullets[i].getPosition().intersects(zombies[j].getPosition())) {
                            bullets[i].stop();
                            if (zombies[j].hit()) {
                                score += 10;
                                if (score >= hiScore) {
                                    hiScore = score;
                                }
                                numZombiesAlive--;
                                if (numZombiesAlive == 0) {
                                    state = State::LEVELING_UP;
                                }
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < numZombies; i++) {
                if (zombies[i].isAlive() && player.getPosition().intersects(zombies[i].getPosition())) {
                    if (player.hit(gameTimeTotal)) {

                    }
                    if (player.getHealth() <= 0) {
                        state = State::GAME_OVER;
                    }
                }
            }

            if (healthPickup.isSpawned() && player.getPosition().intersects(healthPickup.getPosition())) {
                player.increaseHealthLevel(healthPickup.gotIt());
            }
            if (ammoPickup.isSpawned() && player.getPosition().intersects(ammoPickup.getPosition())) {
                bulletsSpare += ammoPickup.gotIt();
            }
        }

        if (state == State::PLAYING) {
            window.clear();
            window.setView(mainView);
            window.draw(background, &textureBackground);
            for (int i = 0; i < numZombies; i++) {
                window.draw(zombies[i].getSprite());
            }
            for (int i = 0; i < NUM_BULLETS; i++) {
                if (bullets[i].isInFlight()) {
                    window.draw(bullets[i].getShape());
                }
            }
            window.draw(player.getSprite());
            if (healthPickup.isSpawned()) {
                window.draw(healthPickup.getSprite());
            }
            if (ammoPickup.isSpawned()) {
                window.draw(ammoPickup.getSprite());
            }
            window.draw(spriteCrosshair);
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
