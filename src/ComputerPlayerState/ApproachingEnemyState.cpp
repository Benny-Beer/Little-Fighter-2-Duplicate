#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"
#include "PlayableObjectStates/ComputerPlayerState/AttackingState.h"
#include "PlayableObjectStates/ComputerPlayerState/PickingUpItemState.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"
#include "PlayableObjectStates/ComputerPlayerState/RetreatingState.h"
#include "PlayableObjectStates/ComputerPlayerState/GotHitState.h"

#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "Objects/PlayableObject.h"
#include <cmath> 
#include <iostream>

ApproachingEnemyState::ApproachingEnemyState(std::shared_ptr<Object> target)
    : m_target(std::move(target)) {
}

void ApproachingEnemyState::enter(PlayableObject& player) {
    
    player.setAniName("walking");

}

void ApproachingEnemyState::update(PlayableObject& player, float deltaTime) {
  
    if (!m_target)
        return;
    if (!player.getTarget()) {
        player.setState(std::make_unique<IdleState>());
        return;
    }
    if (auto object = std::dynamic_pointer_cast<PickableObject>(m_target)) {
        player.setState(std::make_unique<PickingUpItemState>(object));
        return;
    }
    if (auto enemy = std::dynamic_pointer_cast<PlayableObject>(m_target)) {
        if (!enemy->getState()->isAccessible()) {
            m_target = player.getTarget();
        }
    }


    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f direction = m_target->getPosition() - playerPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < player.getAttackRange()) {
        player.setState(std::make_unique<AttackingState>(m_target));
        return;
    }

    // Normalize direction
    if (distance != 0) {
        direction /= distance;
    }
    
    // Move toward enemy
    float speed = player.getSpeed(); 
    player.move(direction * speed * deltaTime);

    if (player.getHeldObj())
    {
        player.getHeldObj()->move(player.getPosition());
    }
}

void ApproachingEnemyState::exit(ComputerPlayer& player) {
}

void ApproachingEnemyState::onHandsAttack(PlayableObject& player) {

    player.setState(std::make_unique<BlockingState>());

}

void ApproachingEnemyState::onStoneHit(PlayableObject& player) {
    player.setState(std::make_unique<GotHitState>());
}
void ApproachingEnemyState::onBoxHit(PlayableObject& player)
{
    player.setState(std::make_unique<KnockedDownState>());
}
void ApproachingEnemyState::onExplosion(PlayableObject& player) {

}
void ApproachingEnemyState::name() {
}
