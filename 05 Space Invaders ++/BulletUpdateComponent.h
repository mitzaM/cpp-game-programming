#pragma once

#include <memory>
#include <string>

#include "GameObject.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "TransformComponent.h"
#include "UpdateComponent.h"


class BulletUpdateComponent : public UpdateComponent
{
private:
    std::string m_SpecificType = "bullet";
    std::shared_ptr<TransformComponent> m_TC;
    std::shared_ptr<RectColliderComponent> m_RCC;

    float m_Speed = 75.0f;

    int m_AlienBulletSpeedModifier;
    int m_ModifierRandomComponent = 5;
    int m_MinimumAdditionalModifier = 5;

    bool m_MovingUp = true;

public:
    bool m_BelongsToPlayer = false;
    bool m_IsSpawned = false;

    void spawn(sf::Vector2f spawnPosition, bool forPlayer);
    void deSpawn();
    bool isMovingUp();

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
