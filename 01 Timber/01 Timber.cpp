#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

void centerText(Text& text);
void drawScene(RenderWindow& window, bool paused);
void initSprite(Texture& texture, Sprite& sprite, float positionX, float positionY);
void moveBranches();
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
const int NUM_DRAWABLES = 12 + NUM_BRANCHES;
const int NUM_MENU_TEXT = 1;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

Sprite branches[NUM_BRANCHES];
Drawable* drawables[NUM_DRAWABLES];
int loaded_drawables = 0;
Text* menu_text[NUM_MENU_TEXT];

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main() {
    VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground;
    initSprite(textureBackground, spriteBackground, 0, 0);

    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    Sprite spriteCloud1;
    initSprite(textureCloud, spriteCloud1, 0, 0);
    bool cloud1Active = false;
    float cloud1Speed = 0.0f;
    Sprite spriteCloud2;
    initSprite(textureCloud, spriteCloud2, 0, 250);
    bool cloud2Active = false;
    float cloud2Speed = 0.0f;
    Sprite spriteCloud3;
    initSprite(textureCloud, spriteCloud3, 0, 500);
    bool cloud3Active = false;
    float cloud3Speed = 0.0f;

    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++) {
        initSprite(textureBranch, branches[i], -2000, -2000);
        branches[i].setOrigin(220, 20);
    }

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree2.png");
    Sprite spriteTree;
    initSprite(textureTree, spriteTree, (SCREEN_WIDTH - textureTree.getSize().x) / 2.0f, 0);

    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    initSprite(texturePlayer, spritePlayer, 580, 720);
    side playerSide = side::LEFT;

    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    initSprite(textureRIP, spriteRIP, 600, 860);

    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    initSprite(textureAxe, spriteAxe, 700, 830);
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    initSprite(textureLog, spriteLog, (SCREEN_WIDTH - textureLog.getSize().x) / 2.0f, 720);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    initSprite(textureBee, spriteBee, 0, 800);
    bool beeActive = false;
    float beeSpeed = 0.0f;

    Clock clock;

    bool paused = true;
    int score = 0;

    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    Text messageText;
    messageText.setFont(font);
    messageText.setString("Press Enter to start!");
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::White);
    centerText(messageText);
    menu_text[0] = &messageText;

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 20);
    drawables[loaded_drawables++] = &scoreText;

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(
        (SCREEN_WIDTH - timeBarStartWidth) / 2.0f,
        SCREEN_HEIGHT - 100
    );
    drawables[loaded_drawables++] = &timeBar;
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            score = 0;
            timeRemaining = 6.0f;
        }

        if (!paused) {
            Time dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {
                paused = true;
                messageText.setString("Out of time!!");
                centerText(messageText);
            }

            if (!beeActive) {
                srand((int)time(0));
                beeSpeed = rand() % 200 + 200.0f;

                srand((int)time(0) * 10);
                float height = rand() % 500 + 500.0f;
                spriteBee.setPosition(SCREEN_WIDTH + 200, height);
                beeActive = true;
            }
            else {
                spriteBee.setPosition(
                    spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y
                );
                if (spriteBee.getPosition().x < -100) {
                    beeActive = false;
                }
            }

            if (!cloud1Active) {
                srand((int)time(0) * 10);
                cloud1Speed = rand() % 200 + 1.0f;

                srand((int)time(0) * 10);
                spriteCloud1.setPosition(-200, (float)(rand() % 150));
                cloud1Active = true;
            }
            else {
                spriteCloud1.setPosition(
                    spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
                    spriteCloud1.getPosition().y
                );
                if (spriteCloud1.getPosition().x > SCREEN_WIDTH) {
                    cloud1Active = false;
                }
            }

            if (!cloud2Active) {
                srand((int)time(0) * 20);
                cloud2Speed = rand() % 200 + 1.0f;

                srand((int)time(0) * 20);
                spriteCloud2.setPosition(-200, (float)(rand() % 300 - 150));
                cloud2Active = true;
            }
            else {
                spriteCloud2.setPosition(
                    spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
                    spriteCloud2.getPosition().y
                );
                if (spriteCloud2.getPosition().x > SCREEN_WIDTH) {
                    cloud2Active = false;
                }
            }

            if (!cloud3Active) {
                srand((int)time(0) * 30);
                cloud3Speed = rand() % 200 + 1.0f;

                srand((int)time(0) * 30);
                spriteCloud3.setPosition(-200, (float)(rand() % 450 - 150));
                cloud3Active = true;
            }
            else {
                spriteCloud3.setPosition(
                    spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
                    spriteCloud3.getPosition().y
                );
                if (spriteCloud3.getPosition().x > SCREEN_WIDTH) {
                    cloud3Active = false;
                }
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            moveBranches();
        }

        drawScene(window, paused);
    }
    return 0;
}

void centerText(Text& text) {
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f
    );
    text.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
}

void drawScene(RenderWindow& window, bool paused) {
    window.clear();
    for (int i = 0; i < loaded_drawables; i++) {
        window.draw(*drawables[i]);
    }

    if (paused) {
        for (int i = 0; i < NUM_MENU_TEXT; i++) {
            window.draw(*menu_text[i]);
        }
    }
    window.display();
}

void initSprite(Texture& texture, Sprite& sprite, float positionX, float positionY) {
    sprite.setTexture(texture);
    sprite.setPosition(positionX, positionY);

    drawables[loaded_drawables++] = &sprite;
}

void moveBranches() {
    for (int i = 0; i < NUM_BRANCHES; i++) {
        float height = i * 150.0f;
        switch (branchPositions[i]) {
        case side::LEFT:
            branches[i].setPosition(610, height);
            branches[i].setRotation(180);
            break;
        case side::RIGHT:
            branches[i].setPosition(1330, height);
            branches[i].setRotation(0);
            break;
        default:
            branches[i].setPosition(3000, height);
            break;
        }
    }
}

void updateBranches(int seed) {
    for (int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    srand((int)time(0) + seed);
    int r = rand() % 5;

    switch (r) {
    case 0:
        branchPositions[0] = side::LEFT;
        break;
    case 1:
        branchPositions[0] = side::RIGHT;
        break;
    default:
        branchPositions[0] = side::NONE;
        break;
    }
}
