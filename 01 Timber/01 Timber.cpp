#include <SFML/Graphics.hpp>

using namespace sf;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main() {
    VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree2.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(
        (float)((SCREEN_WIDTH - textureTree.getSize().x)/2), 0
    );

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeActive = false;
    float beeSpeed = 0.0f;

    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 0);
    Sprite spriteCloud2;
    spriteCloud2.setTexture(textureCloud);
    spriteCloud2.setPosition(0, 250);
    Sprite spriteCloud3;
    spriteCloud3.setTexture(textureCloud);
    spriteCloud3.setPosition(0, 500);

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    Clock clock;

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

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

        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(spriteBee);

        window.display();
    }

    return 0;
}
