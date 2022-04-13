#pragma once

#include <memory>
#include <string>

#include "GameObject.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "TransformComponent.h"
#include "UpdateComponent.h"


class PlayerUpdateComponent : public UpdateComponent
{
private:
    std::string m_SpecificType = "player";

    std::shared_ptr<TransformComponent> m_TC;
    std::shared_ptr<RectColliderComponent> m_RCC;

    float m_Speed = 50.0f;
    float m_XExtent = 0;
    float m_YExtent = 0;

    bool m_IsHoldingLeft = false;
    bool m_IsHoldingRight = false;
    bool m_IsHoldingUp = false;
    bool m_IsHoldingDown = false;

public:
    void updateShipTravelWithController(float x, float y);

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    std::string Component::getSpecificType()
    {
        return m_SpecificType;
    }

    void Component::start(GameObjectSharer* gos, GameObject* self)
    {
        m_TC = std::static_pointer_cast<TransformComponent>(
            self->getComponentByTypeAndSpecificType("transform", "transform")
        );
        m_RCC = std::static_pointer_cast<RectColliderComponent>(
            self->getComponentByTypeAndSpecificType("collider", "rect")
        );
    }

    void update(float fps) override;
};
