#include <memory>
#include <string>
#include <vector>

#include "BulletUpdateComponent.h"
#include "DevelopState.h"
#include "InvaderUpdateComponent.h"
#include "PhysicsEnginePlayMode.h"
#include "SoundEngine.h"
#include "WorldState.h"


void PhysicsEnginePlayMode::detectInvaderCollisions(std::vector<GameObject>& objects, const std::vector<int>& bulletPositions)
{
    sf::Vector2f offScreen(-1, -1);

    for (auto invaderIt = objects.begin(); invaderIt != objects.end(); ++invaderIt) {
        if ((*invaderIt).isActive() && (*invaderIt).getTag() == "invader") {
            auto bulletIt = objects.begin();
            std::advance(bulletIt, bulletPositions[0]);
            for (bulletIt; bulletIt != objects.end(); ++bulletIt) {
                if ((*invaderIt).getEncompassingRectCollider().intersects((*bulletIt).getEncompassingRectCollider()) && (*bulletIt).getTag() == "bullet" && std::static_pointer_cast<BulletUpdateComponent>((*bulletIt).getFirstUpdateComponent())->m_BelongsToPlayer) {
                    SoundEngine::playInvaderExplode();
                    (*invaderIt).getTransformComponent()->getLocation() = offScreen;
                    (*bulletIt).getTransformComponent()->getLocation() = offScreen;
                    WorldState::SCORE++;
                    WorldState::NUM_INVADERS--;
                    (*invaderIt).setInactive();
                }
            }
        }
    }
}


void PhysicsEnginePlayMode::detectPlayerCollisionsAndInvaderDirection(std::vector<GameObject>& objects, const std::vector<int>& bulletPositions)
{
    sf::Vector2f offScreen(-1, -1);
    sf::FloatRect playerCollider = m_Player->getEncompassingRectCollider();
    std::shared_ptr<TransformComponent> playerTransform = m_Player->getTransformComponent();
    sf::Vector2f playerLocation = playerTransform->getLocation();

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        std::string currentTag = (*it).getTag();
        if ((*it).isActive() && (*it).hasCollider() && currentTag != "Player") {
            sf::FloatRect currentCollider = (*it).getEncompassingRectCollider();
            if (currentCollider.intersects(playerCollider)) {
                if (currentTag == "bullet") {
                    SoundEngine::playPlayerExplode();
                    WorldState::LIVES--;
                    (*it).getTransformComponent()->getLocation() = offScreen;
                }
                if (currentTag == "invader") {
                    SoundEngine::playPlayerExplode();
                    SoundEngine::playInvaderExplode();
                    WorldState::LIVES--;
                    (*it).getTransformComponent()->getLocation() = offScreen;
                    WorldState::SCORE++;
                    (*it).setInactive();
                }
            }

            std::shared_ptr<TransformComponent> currentTransform = (*it).getTransformComponent();
            sf::Vector2f currentLocation = currentTransform->getLocation();
            sf::Vector2f currentSize = currentTransform->getSize();

            if (currentTag == "invader") {
                if (!m_NeedToDropDownAndReverse && !m_InvaderHitWallThisFrame) {
                    bool movingRight = std::static_pointer_cast<InvaderUpdateComponent>(
                        (*it).getFirstUpdateComponent()
                    )->isMovingRight();
                    if (currentLocation.x >= WorldState::WORLD_HEIGHT - currentSize.x) {
                        if (movingRight) {
                            m_InvaderHitWallThisFrame = true;
                        }
                    } else if (currentLocation.x < 0) {
                        if (!movingRight) {
                            m_InvaderHitWallThisFrame = true;
                        }
                    }
                } else if (m_NeedToDropDownAndReverse && !m_InvaderHitWallPreviousFrame) {
                    if ((*it).hasUpdateComponent()) {
                        std::static_pointer_cast<InvaderUpdateComponent>((*it).getFirstUpdateComponent())->dropDownAndReverse();
                    }
                }
            }
        }
    }
}
