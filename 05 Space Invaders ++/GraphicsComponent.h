#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "Component.h"
#include "GameObjectSharer.h"
#include "TransformComponent.h"


class GraphicsComponent : public Component
{
private:
    std::string m_Type = "graphics";
    bool m_Enabled = false;

public:
    virtual void draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t) = 0;
    virtual void initialiseGraphics(std::string bitmapName, sf::Vector2f objectSize) = 0;

    std::string Component::getType()
    {
        return m_Type;
    }

    void Component::disableComponent()
    {
        m_Enabled = false;
    }

    void Component::enableComponent()
    {
        m_Enabled = true;
    }

    bool Component::enabled()
    {
        return m_Enabled;
    }

    void Component::start(GameObjectSharer* gos, GameObject* self) {}
};
