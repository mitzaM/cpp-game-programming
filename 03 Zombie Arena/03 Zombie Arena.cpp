#include <fstream>
#include <sstream>

#include <SFML/Audio.hpp>
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
    Bullet* bullets = new Bullet[NUM_BULLETS];
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

    sf::Sprite spriteGameOver;
    sf::Texture textureGameOver = TextureHolder::GetTexture("graphics/background.png");
    spriteGameOver.setTexture(textureGameOver);
    spriteGameOver.setPosition(0, 0);

    sf::View hudView(sf::FloatRect(0, 0, (float)resolution.x, (float)resolution.y));

    sf::Sprite spriteAmmoIcon;
    sf::Texture textureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
    spriteAmmoIcon.setTexture(textureAmmoIcon);
    spriteAmmoIcon.setPosition(20, 980);

    sf::RectangleShape healthBar;
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(450, 980);

    sf::Font font;
    font.loadFromFile("fonts/zombiecontrol.ttf");

    sf::Text pausedText;
    pausedText.setFont(font);
    pausedText.setCharacterSize(155);
    pausedText.setFillColor(sf::Color::White);
    pausedText.setPosition(400, 400);
    pausedText.setString("Press enter \nto continue");

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(125);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(250, 850);
    gameOverText.setString("Press Enter to play");

    sf::Text levelUpText;
    levelUpText.setFont(font);
    levelUpText.setCharacterSize(80);
    levelUpText.setFillColor(sf::Color::White);
    levelUpText.setPosition(150, 250);
    std::stringstream levelUpStream;
    levelUpStream <<
        "1 - Increased rate of fire" <<
        "\n2 - Increased clip size (next reload)" <<
        "\n3 - Increased max health" <<
        "\n4 - Increased run speed" <<
        "\n5 - More and better health pickups" <<
        "\n6 - More and better ammo pickups";
    levelUpText.setString(levelUpStream.str());

    sf::Text ammoText;
    ammoText.setFont(font);
    ammoText.setCharacterSize(55);
    ammoText.setFillColor(sf::Color::White);
    ammoText.setPosition(200, 980);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(55);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20, 0);

    std::ifstream inputFile("gamedata/scores.txt");
    if (inputFile.is_open()) {
        inputFile >> hiScore;
        inputFile.close();
    }

    sf::Text hiScoreText;
    hiScoreText.setFont(font);
    hiScoreText.setCharacterSize(55);
    hiScoreText.setFillColor(sf::Color::White);
    hiScoreText.setPosition(1400, 0);
    std::stringstream hiScoreStream;
    hiScoreStream << "Hi score: " << hiScore;
    hiScoreText.setString(hiScoreStream.str());

    sf::Text zombiesRemainingText;
    zombiesRemainingText.setFont(font);
    zombiesRemainingText.setCharacterSize(55);
    zombiesRemainingText.setFillColor(sf::Color::White);
    zombiesRemainingText.setPosition(1500, 980);
    zombiesRemainingText.setString("Zombies: 100");

    int wave = 0;
    sf::Text waveNumberText;
    waveNumberText.setFont(font);
    waveNumberText.setCharacterSize(55);
    waveNumberText.setFillColor(sf::Color::White);
    waveNumberText.setPosition(1250, 980);
    waveNumberText.setString("Wave: 0");

    int framesSinceLastHUDUpdate = 0;
    int fpsMeasurementFrameInterval = 1000;

    sf::SoundBuffer hitBuffer;
    hitBuffer.loadFromFile("sound/hit.wav");
    sf::Sound hit(hitBuffer);

    sf::SoundBuffer splatBuffer;
    splatBuffer.loadFromFile("sound/splat.wav");
    sf::Sound splat(splatBuffer);

    sf::SoundBuffer shootBuffer;
    shootBuffer.loadFromFile("sound/shoot.wav");
    sf::Sound shoot(shootBuffer);

    sf::SoundBuffer reloadBuffer;
    reloadBuffer.loadFromFile("sound/reload.wav");
    sf::Sound reload(reloadBuffer);

    sf::SoundBuffer reloadFailedBuffer;
    reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
    sf::Sound reloadFailed(reloadFailedBuffer);

    sf::SoundBuffer powerupBuffer;
    powerupBuffer.loadFromFile("sound/powerup.wav");
    sf::Sound powerup(powerupBuffer);

    sf::SoundBuffer pickupBuffer;
    pickupBuffer.loadFromFile("sound/pickup.wav");
    sf::Sound pickup(pickupBuffer);

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

                        std::ofstream outputFile("gamedata/scores.txt");
                        outputFile << hiScore;
                        outputFile.close();
                    }
                }
            }

            if (healthPickup.isSpawned() && player.getPosition().intersects(healthPickup.getPosition())) {
                player.increaseHealthLevel(healthPickup.gotIt());
            }
            if (ammoPickup.isSpawned() && player.getPosition().intersects(ammoPickup.getPosition())) {
                bulletsSpare += ammoPickup.gotIt();
            }

            healthBar.setSize(sf::Vector2f(player.getHealth() * 3.0f, 50.0f));
            framesSinceLastHUDUpdate++;

            if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval) {
                std::stringstream ssAmmo, ssScore, ssHiScore, ssWave, ssZombiesAlive;

                ssAmmo << bulletsInClip << "/" << bulletsSpare;
                ammoText.setString(ssAmmo.str());

                ssScore << "Score: " << score;
                scoreText.setString(ssScore.str());

                ssHiScore << "Hi score: " << hiScore;
                hiScoreText.setString(ssHiScore.str());

                ssWave << "Wave: " << wave;
                waveNumberText.setString(ssWave.str());

                ssZombiesAlive << "Zombies: " << numZombiesAlive;
                zombiesRemainingText.setString(ssZombiesAlive.str());

                framesSinceLastHUDUpdate = 0;
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

            window.setView(hudView);
            window.draw(spriteAmmoIcon);
            window.draw(ammoText);
            window.draw(scoreText);
            window.draw(hiScoreText);
            window.draw(healthBar);
            window.draw(waveNumberText);
            window.draw(zombiesRemainingText);
        }
        if (state == State::LEVELING_UP) {
            window.draw(spriteGameOver);
            window.draw(levelUpText);
        }
        if (state == State::PAUSED) {
            window.draw(pausedText);
        }
        if (state == State::GAME_OVER) {
            window.draw(spriteGameOver);
            window.draw(gameOverText);
            window.draw(scoreText);
            window.draw(hiScoreText);
        }
        window.display();
    }

    delete[] bullets;
    delete[] zombies;
    return 0;
}
