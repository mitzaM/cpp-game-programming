#include <SFML/Graphics.hpp>

using namespace sf;

void drawScene(RenderWindow &window);
void initSprite(Texture &texture, Sprite &sprite, float positionX, float positionY);

const int NUM_SPRITES = 6;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

Sprite *sprites[NUM_SPRITES];
int loaded_sprites = 0;

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

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree2.png");
    float treeCenterX = (float)((SCREEN_WIDTH - textureTree.getSize().x) / 2);
    Sprite spriteTree;
    initSprite(textureTree, spriteTree, treeCenterX, 0);

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");

    Sprite spriteBee;
    initSprite(textureBee, spriteBee, 0, 800);
    bool beeActive = false;
    float beeSpeed = 0.0f;

    Clock clock;

    bool paused = true;

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
        }

        if (!paused) {
            Time dt = clock.restart();

            if (!beeActive) {
                srand((int)time(0));
                beeSpeed = (float)(rand() % 200 + 200);

                srand((int)time(0) * 10);
                float height = (float)(rand() % 500 + 500);
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
                cloud1Speed = (float)(rand() % 200);

                srand((int)time(0) * 10);
                float height = (float)(rand() % 150);
                spriteCloud1.setPosition(-200, height);
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
                cloud2Speed = (float)(rand() % 200);

                srand((int)time(0) * 20);
                float height = (float)(rand() % 300 - 150);
                spriteCloud2.setPosition(-200, height);
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
                cloud3Speed = (float)(rand() % 200);

                srand((int)time(0) * 30);
                float height = (float)(rand() % 450 - 150);
                spriteCloud3.setPosition(-200, height);
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
        }

        drawScene(window);
    }

    return 0;
}

void drawScene(RenderWindow &window)
{
    window.clear();

    for (int i = 0; i < NUM_SPRITES; i++) {
        window.draw(*sprites[i]);
    }

    window.display();
}

void initSprite(Texture& texture, Sprite& sprite, float positionX, float positionY) {
    sprite.setTexture(texture);
    sprite.setPosition(positionX, positionY);
    sprites[loaded_sprites] = &sprite;
    loaded_sprites++;
}
