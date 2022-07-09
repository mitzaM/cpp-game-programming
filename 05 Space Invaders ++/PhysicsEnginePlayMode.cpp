#include <memory>
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
