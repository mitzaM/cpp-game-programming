#include <memory>
#include <vector>

#include "BulletUpdateComponent.h"
#include "GameObjectFactoryPlayMode.h"
#include "InvaderUpdateComponent.h"
#include "PlayerUpdateComponent.h"
#include "RectColliderComponent.h"
#include "StandardGraphicsComponent.h"
#include "TransformComponent.h"


void GameObjectFactoryPlayMode::buildGameObject(GameObjectBlueprint& bp, std::vector<GameObject>& gameObjects)
{
    GameObject gameObject;
    gameObject.setTag(bp.getName());

    for (auto it = bp.getComponentList().begin(); it != bp.getComponentList().end(); ++it) {
        if (*it == "Transform") {
            gameObject.addComponent(
                std::make_shared<TransformComponent>(
                    bp.getWidth(),
                    bp.getHeight(),
                    sf::Vector2f(bp.getLocationX(), bp.getLocationY())
                )
            );
        } else if (*it == "Player Update") {
            gameObject.addComponent(std::make_shared<PlayerUpdateComponent>());
        } else if (*it == "Invader Update") {
            gameObject.addComponent(std::make_shared<InvaderUpdateComponent>());
        } else if (*it == "Bullet Update") {
            gameObject.addComponent(std::make_shared<BulletUpdateComponent>());
        } else if (*it == "Standard Graphics") {
            std::shared_ptr<StandardGraphicsComponent> sgp = std::make_shared<StandardGraphicsComponent>();
            gameObject.addComponent(sgp);
            sgp->initialiseGraphics(
                bp.getBitmapName(),
                sf::Vector2f(bp.getWidth(), bp.getHeight())
            );
        }
    }

    if (bp.getEncompassingRectCollider()) {
        std::shared_ptr<RectColliderComponent> rcc = std::make_shared<RectColliderComponent>(
            bp.getEncompassingRectColliderLabel()
        );
        gameObject.addComponent(rcc);
        rcc->setOrMoveCollider(
            bp.getLocationX(),
            bp.getLocationY(),
            bp.getWidth(),
            bp.getHeight()
        );
    }
    gameObjects.push_back(gameObject);
}
