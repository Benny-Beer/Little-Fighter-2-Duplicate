#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"
#include "PlayableObjectStates/ComputerPlayerState/AttackingState.h"
#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "Objects/PlayableObject.h"
#include <cmath> // sqrt, etc.
#include <iostream>

ApproachingEnemyState::ApproachingEnemyState(PlayableObject* target)
    : m_target(std::move(target)) {
    //std::cout << target->getPosition().x << "." << target->getPosition().y << std::endl;
}

void ApproachingEnemyState::enter(PlayableObject& player) {
    //std::cout << "enter:: ApproachingEnemyState\n";
    

    //Animation approachingEnemyAnim(player.getTexture(),
    //    320, 0,          // x, y
    //    80, 80,        // width, height
    //    4,             // מספר פריימים
    //    0.2f);         // זמן בין פריימים

    //player.setAnimation(approachingEnemyAnim);
    player.setAniName("walking");
    //player.setDiraction(m_input); 
}

void ApproachingEnemyState::update(PlayableObject& player, float deltaTime) {
    if (!m_target)
        return;
    // std::cout << player.getName() << " - MY TARGET NAME IS: " << m_target->getName() << std::endl;

    //if (player.isAttacked()) {
    //    player.setState(std::make_unique<BlockingState>());
    //    return;
    //}

    sf::Vector2f playerPos = player.getPosition();
    PlayableObject* target = player.getTarget();
    sf::Vector2f direction = target->getPosition() - playerPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    //std::cout << "[ApproachingEnemyState] " << player.getName() << " distance to " << m_target->getName() << ":" << distance << std::endl;

    if (distance < 50.f /* && (playerPos.x - target->getPosition().x) == 0.f*/) {
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

    if (player.getObject())
    {
        std::cout << player.getName() << " was here!!1\n";
        player.getObject()->move(player.getPosition());
    }
}

void ApproachingEnemyState::exit(ComputerPlayer& player) {
    // Optional: stop movement, reset animation, etc.
}

void ApproachingEnemyState::onHandsAttack(PlayableObject& player) {
    std::cout << player.getName() << " is in [ApproachingEnemyState] and i got attacked by hands\n"
        "activating blocking state\n";
    player.setState(std::make_unique<BlockingState>());
}