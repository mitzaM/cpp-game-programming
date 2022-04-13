#include <iostream>
#include <memory>
#include <string>

#include "DevelopState.h"
#include "GameObject.h"
#include "RectColliderComponent.h"
#include "UpdateComponent.h"


void GameObject::update(float fps)
{
    if (m_Active && m_HasUpdateComponent) {
        for (int i = m_FirstUpdateComponentLocation; i < m_FirstUpdateComponentLocation + m_NumberUpdateComponents; i++) {
            std::shared_ptr<UpdateComponent> tempUpdate = std::static_pointer_cast<UpdateComponent>(m_Components[i]);
            if (tempUpdate->enabled()) {
                tempUpdate->update(fps);
            }
        }
    }
}

void GameObject::draw(sf::RenderWindow& window)
{
    if (m_Active && m_HasGraphicsComponent && m_Components[m_GraphicsComponentLocation]->enabled()) {
        getGraphicsComponent()->draw(window, getTransformComponent());
    }
}

std::shared_ptr<GraphicsComponent> GameObject::getGraphicsComponent()
{
    return std::static_pointer_cast<GraphicsComponent>(m_Components[m_GraphicsComponentLocation]);
}

std::shared_ptr<TransformComponent> GameObject::getTransformComponent()
{
    return std::static_pointer_cast<TransformComponent>(m_Components[m_TransformComponentLocation]);
}

void GameObject::addComponent(std::shared_ptr<Component> component)
{
    m_Components.push_back(component);
    component->enableComponent();

    if (component->getType() == "update") {
        m_HasUpdateComponent = true;
        m_NumberUpdateComponents++;
        if (m_NumberUpdateComponents == 1) {
            m_FirstUpdateComponentLocation = m_Components.size() - 1;
        }
    } else if (component->getType() == "graphics") {
        m_HasGraphicsComponent = true;
        m_GraphicsComponentLocation = m_Components.size() - 1;
    } else if (component->getType() == "transform") {
        m_TransformComponentLocation = m_Components.size() - 1;
    } else if (component->getType() == "collider" && component->getSpecificType() == "rect") {
        m_HasCollider = true;
        m_NumberRectColliderComponents++;
        if (m_NumberRectColliderComponents == 1) {
            m_FirstRectColliderComponentLocation = m_Components.size() - 1;
        }
    }
}

void GameObject::setActive()
{
    m_Active = true;
}

void GameObject::setInactive()
{
    m_Active = false;
}

bool GameObject::isActive()
{
    return m_Active;
}

void GameObject::setTag(std::string tag)
{
    m_Tag = "" + tag;
}

std::string GameObject::getTag()
{
    return m_Tag;
}

void GameObject::start(GameObjectSharer* gos)
{
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        (*it)->start(gos, this);
    }
}

std::shared_ptr<Component> GameObject::getComponentByTypeAndSpecificType(std::string type, std::string specificType)
{
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        if ((*it)->getType() == type && (*it)->getSpecificType() == specificType) {
            return *it;
        }
    }

    #ifdef debuggingErrors
    cout << "GameObject.cpp::getComponentByTypeAndSpecificType-" << "COMPONENT NOT FOUND ERROR!" << endl;
    #endif // debuggingErrors

    return m_Components[0];
}

sf::FloatRect& GameObject::getEncompassingRectCollider()
{
    if (m_HasCollider) {
        return std::static_pointer_cast<RectColliderComponent>(m_Components[m_FirstRectColliderComponentLocation])->getColliderRectF();
    }
}

std::string GameObject::getEncompassingRectColliderTag()
{
    return std::static_pointer_cast<RectColliderComponent>(m_Components[m_FirstRectColliderComponentLocation])->getColliderTag();
}

std::shared_ptr<UpdateComponent> GameObject::getFirstUpdateComponent()
{
    return std::static_pointer_cast<UpdateComponent>(m_Components[m_FirstUpdateComponentLocation]);
}

bool GameObject::hasCollider()
{
    return m_HasCollider;
}

bool GameObject::hasUpdateComponent()
{
    return m_HasUpdateComponent;
}
