#include "PlayableObjectStates/ComputerPlayerState/PickingUpItemState.h"
#include "GamePlay/ComputerPlayer.h"
#include "Objects/PickableObject.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"

#include <SFML/System/Vector2.hpp>
#include <cmath>

PickingUpItemState::PickingUpItemState(std::shared_ptr<Object> item)
    : m_target(std::move(item)) {}

void PickingUpItemState::enter(PlayableObject& player) {
    
    player.setAniName("walking");
}

void PickingUpItemState::update(PlayableObject& player, float deltaTime) {
    

    if (auto object = std::dynamic_pointer_cast<PlayableObject>(m_target)) {
        player.setState(std::make_unique<ApproachingEnemyState>(m_target));
        return;
    }

    m_targetItem = std::dynamic_pointer_cast<PickableObject>(m_target);
    std::cout << "Target typeid: " << typeid(*m_target).name() << std::endl;
    std::cout << "TargetItem typeid: " << typeid(*m_targetItem).name() << std::endl;
    if (m_targetItem->onEarth())
        std::cout << "OFCOURSE\n";
    else
        std::cout << "NAAH\n";
    if (!m_targetItem ||!m_targetItem->onEarth()) {
        // Item already gone – return to idle
        m_targetItem = nullptr;
        player.wantItem();
        
        player.setState(std::make_unique<IdleState>());
        return;
    }

    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f itemPos = m_targetItem->getPosition();

    float distance = std::sqrt(std::pow(playerPos.x - itemPos.x, 2) +
        std::pow(playerPos.y - itemPos.y, 2));

    const float pickupRange = 40.f;

    if (distance <= pickupRange) {
        // Pick up item
        //player.pickUp(*m_targetItem);
        player.pickUpObject(m_targetItem);
        player.setStrategyName(m_targetItem->getName());
        m_targetItem->pick();
        player.adjustRange(m_targetItem->getRange());
        std::cout << player.getDirection() << "and " << player.getPosition().y << " picked item up\n";
        player.tookItem();
        player.setState(std::make_unique<IdleState>());
    }
    else {
        // Move toward item
        sf::Vector2f direction = itemPos - playerPos;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0.f)
            direction /= length;

        player.move(direction * player.getSpeed() * deltaTime);
    }
}

void PickingUpItemState::exit(ComputerPlayer& player) {
    // No cleanup needed for now
}

void PickingUpItemState::name() {
    std::cout << "PickingUpItemState" << std::endl;
}
