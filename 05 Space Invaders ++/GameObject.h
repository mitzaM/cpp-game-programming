#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Component.h"
#include "GameObjectSharer.h"
#include "GraphicsComponent.h"
#include "UpdateComponent.h"


class GameObject
{
private:
    std::vector<std::shared_ptr<Component>> m_Components;

    std::string m_Tag;
    bool m_Active = false;

    bool m_HasUpdateComponent = false;
    int m_NumberUpdateComponents = 0;
    int m_FirstUpdateComponentLocation = -1;

    bool m_HasGraphicsComponent = false;
    int m_GraphicsComponentLocation = -1;
    int m_TransformComponentLocation = -1;

    bool m_HasCollider = false;
    int m_NumberRectColliderComponents = 0;
    int m_FirstRectColliderComponentLocation = -1;

public:
    void update(float fps);
    void draw(sf::RenderWindow& window);
    void addComponent(std::shared_ptr<Component> component);

    void setActive();
    void setInactive();
    bool isActive();
    void setTag(std::string tag);
    std::string getTag();

    void start(GameObjectSharer* gos);

    std::shared_ptr<Component> getComponentByTypeAndSpecificType(std::string type, std::string specificType);

    bool hasCollider();
    bool hasUpdateComponent();
    sf::FloatRect& getEncompassingRectCollider();
    std::string getEncompassingRectColliderTag();

    std::shared_ptr<GraphicsComponent> getGraphicsComponent();
    std::shared_ptr<TransformComponent> getTransformComponent();
    std::shared_ptr<UpdateComponent> getFirstUpdateComponent();
};
