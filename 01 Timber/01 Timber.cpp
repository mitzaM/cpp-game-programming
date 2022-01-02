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
        (SCREEN_WIDTH - textureTree.getSize().x)/2, 0
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

    Clock clock;

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        Time dt = clock.restart();

        if (!beeActive) {
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;

            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
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
