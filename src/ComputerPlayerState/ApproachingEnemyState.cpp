#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"
#include "PlayableObjectStates/ComputerPlayerState/AttackingState.h"
#include "PlayableObjectStates/ComputerPlayerState/PickingUpItemState.h"

#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "Objects/PlayableObject.h"
#include <cmath> // sqrt, etc.
#include <iostream>

ApproachingEnemyState::ApproachingEnemyState(std::shared_ptr<Object> target)
    : m_target(std::move(target)) {
    //std::cout << target->getPosition().x << "." << target->getPosition().y << std::endl;
}

void ApproachingEnemyState::enter(PlayableObject& player) {
    
    player.setAniName("walking");
    //player.setDiraction(m_input); 
}

void ApproachingEnemyState::update(PlayableObject& player, float deltaTime) {
  
    if (!m_target)
        return;
    if (auto object = std::dynamic_pointer_cast<PickableObject>(m_target)) {
        player.setState(std::make_unique<PickingUpItemState>(object));
        return;
    }
    // std::cout << player.getName() << " - MY TARGET NAME IS: " << m_target->getName() << std::endl;

    //if (player.isAttacked()) {
    //    player.setState(std::make_unique<BlockingState>());
    //    return;
    //}

    sf::Vector2f playerPos = player.getPosition();
    //std::shared_ptr<Object> target = player.getTarget();
    sf::Vector2f direction = m_target->getPosition() - playerPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    //std::cout << "[ApproachingEnemyState] " << player.getName() << " distance to " << m_target->getName() << ":" << distance << std::endl;

    if (distance < player.getAttackRange() /* && (playerPos.x - target->getPosition().x) == 0.f*/) {
        player.setState(std::make_unique<AttackingState>(m_target));
        return;
    }

    // Normalize direction
    if (distance != 0) {
        direction /= distance;
    }
    //
    // Move toward enemy
    float speed = player.getSpeed(); 
    player.move(direction * speed * deltaTime);

    if (player.getHeldObj())
    {

        std::cout << player.getName() << " was here!!1\n";
        player.getHeldObj()->move(player.getPosition());
    }
   // std::cout << "im at the end\n" << "because " << m_target->getPosition().x << "\n";
}

void ApproachingEnemyState::exit(ComputerPlayer& player) {
    // Optional: stop movement, reset animation, etc.
}

void ApproachingEnemyState::onHandsAttack(PlayableObject& player) {
    std::cout << player.getName() << " is in [ApproachingEnemyState] and i got attacked by hands\n"
        "activating blocking state\n";
    player.setState(std::make_unique<BlockingState>());
}
void ApproachingEnemyState::name() {
    std::cout << "ApproachingEnemyState" << std::endl;
}
