#include "PlayableObjectStates/ComputerPlayerState/AttackingState.h"
#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"
#include "PlayableObjectStates/ComputerPlayerState/PickingUpItemState.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include "PlayableObjectStates/ComputerPlayerState/RetreatingState.h"
#include "PlayableObjectStates/ComputerPlayerState/GotHitState.h"
#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"



#include "GamePlay/ComputerPlayer.h"
#include "Objects/PlayableObject.h"
#include "EventCommands/HandsAttackCommand.h"
#include <memory>
#include <cmath>

AttackingState::AttackingState(std::shared_ptr<Object> target)
    : m_target(std::move(target)) {
    m_attackCooldown = 0.2f; // Start immediately
}

void AttackingState::enter(PlayableObject& player) {
    std::cout << "enter:: AttackingState\n";

    //auto target = std::dynamic_pointer_cast<PlayableObject>(m_target);
    

    alignAttacker(player);
    player.setAniName("attacking");
    player.attack();
    player.adjustRange(50.f);
    player.setStrategyName("");

    player.wantItem();
    
    if (auto target = std::dynamic_pointer_cast<PlayableObject>(m_target))
        target->handleCommand(std::make_unique<HandsAttackCommand>());
    // I think we need switch-case here according to the attack
    //player.setDiraction(m_input);     
    
}

void AttackingState::update(PlayableObject& player, float deltaTime) {

    if (!m_target)
        return;

    if (!player.getTarget()) {
        player.setState(std::make_unique<IdleState>());
        return;
    }
    if (auto enemy = std::dynamic_pointer_cast<PlayableObject>(m_target)) {
        if (!enemy->getState()->isAccessible()) {
            m_target = player.getTarget();
        }
    }
    std::cout << 95 << "\n";

    //std::cout << player.getName() <<" - MY TARGET NAME IS: " << m_target->getName() << std::endl;
    player.setAniName("attacking");

    sf::Vector2f playerPos = player.getPosition();

    sf::Vector2f targetPos = m_target->getPosition();


    float distance = std::sqrt(std::pow(playerPos.x - targetPos.x, 2) +
        std::pow(playerPos.y - targetPos.y, 2));
    //std::cout << targetPos.x << std::endl;
    //std::cout << "[AttackingState] " << player.getName() << " distance to " << m_target->getName() << ":" << distance << std::endl;

    // Check if still in attack range
    const float attackRange = 150.f;
    if (distance > player.getAttackRange()) {
        // Too far — switch back to approach state
        std::cout << "here? range is: " << player.getAttackRange() << "\n";
        player.setState(std::make_unique<ApproachingEnemyState>(m_target));
        return;
    }



    // Countdown attack cooldown
    if (m_attackCooldown > 0) {
        m_attackCooldown -= deltaTime;
        return;
    }
    /*else {
        if (player.getObject()) {
        }
        else {

        }
        if (player.getTarget())
            std::cout << "OFCOURSE\n";
        else 
            std::cout << "NAAH\n";
        player.setState(std::make_unique<IdleState>());
        return;
    }*/

    // Perform attack - TODO the logic
    //player.performAttack(*m_target);

    // Reset cooldown
    //m_attackCooldown = 1.0f; // One second between attacks
}

void AttackingState::exit(ComputerPlayer& player) {
    // Stop attack animation or cleanup if needed
}

void AttackingState::alignAttacker(PlayableObject& player)
{
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f targetPos = m_target->getPosition();

    // ùåîøéí òì àåúå X, îééùøéí ìÎY, áîøç÷ attackRange îäéøéá
    float dx = playerPos.x - targetPos.x;
    float sign = (dx >= 0) ? -1.f : 1.f; // àéæä öã ùì äîåú÷ó?
    // float alignedX = targetPos.x + sign * 80.f; --> MAKING PROBLEM OF ATTACK AMINATION TO THE WRONG SIDE
    float alignedY = targetPos.y; // ééùåø îãåé÷, àå áúåê èåìøðñ ÷èï

    player.setPosition({ playerPos.x, alignedY }); // suppose to be alignedX
}

void AttackingState::name() {
    std::cout << "AttackingState" << std::endl;
}

void AttackingState::onHandsAttack(PlayableObject& player)
{
    std::cout << "im in attacking\n";
    player.setState(std::make_unique<BlockingState>());
}
void AttackingState::onStoneHit(PlayableObject& player) {
    std::cout << player.getName() << " inAttackingState::onStoneHit\n";
	player.setState(std::make_unique<GotHitState>());

}
void AttackingState::onExplosion(PlayableObject& player) {


}