#include <memory>
#include <string>

#include "BitmapStore.h"
#include "StandardGraphicsComponent.h"


void StandardGraphicsComponent::initialiseGraphics(std::string bitmapName, sf::Vector2f objectSize)
{
    std::string bitmapPath = "graphics/" + bitmapName + ".png";
    BitmapStore::addBitmap(bitmapPath);
    m_Sprite.setTexture(BitmapStore::getBitmap(bitmapPath));

    auto textureSize = m_Sprite.getTexture()->getSize();
    m_Sprite.setScale(float(objectSize.x) / textureSize.x, float(objectSize.y) / textureSize.y);
    m_Sprite.setColor(sf::Color(0, 255, 0));
}

void StandardGraphicsComponent::draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t)
{
    m_Sprite.setPosition(t->getLocation());
    window.draw(m_Sprite);
}
