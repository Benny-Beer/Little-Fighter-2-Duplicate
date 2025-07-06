#include "PlayableObjectStates/ComputerPlayerState/AttackingState.h"
#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"
#include "PlayableObjectStates/ComputerPlayerState/PickingUpItemState.h"

#include "GamePlay/ComputerPlayer.h"
#include "Objects/PlayableObject.h"
#include "EventCommands/HandsAttackCommand.h"
#include <memory>
#include <cmath>

AttackingState::AttackingState(PlayableObject* target)
    : m_target(std::move(target)) {
    m_attackCooldown = 0.2f; // Start immediately
}

void AttackingState::enter(PlayableObject& player) {
    //std::cout << "enter:: AttackingState\n";

    //Animation attackingAnim(player.getTexture(),
    //    80, 0,          // x, y
    //    80, 80,        // width, height
    //    6,             // מספר פריימים
    //    0.2f);         // זמן בין פריימים

    //player.setAnimation(attackingAnim);
    m_target = player.getTarget();
    //sf::Vector2f attackerPos = player.getPosition();
    //sf::Vector2f targetPos = m_target->getPosition();
    //player.setPosition({ targetPos.x, targetPos.y });
    alignAttacker(player);
    player.setAniName("attacking");
    if (player.getObject()) {
        std::cout << "before attack: YES!\n";
    }
    else {
        std::cout << "before attack: NO!\n";

    }
    player.attack();
    player.wantItem();

    if (player.getObject()) {
        std::cout << "after attack: YES!\n";
    }
    else {
        std::cout << "after attack: NO!\n";

    }
    m_target->handleCommand(std::make_unique<HandsAttackCommand>());
    // I think we need switch-case here according to the attack
    //player.setDiraction(m_input);     
    
}

void AttackingState::update(PlayableObject& player, float deltaTime) {
    if (!m_target)
        return;
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
    if (distance > attackRange) {
        // Too far — switch back to approach state
        player.setState(std::make_unique<ApproachingEnemyState>(m_target));
        return;
    }



    // Countdown attack cooldown
    if (m_attackCooldown > 0) {
        std::cout << "im NOT switching!!! " << m_attackCooldown << std::endl;

        m_attackCooldown -= deltaTime;
        return;
    }
    else {
        std::cout << "im switching!!!\n";
        if (player.getObject()) {
            std::cout << "YES!\n";
        }
        else {
            std::cout << "NO!\n";

        }
        player.setState(std::make_unique<PickingUpItemState>(player.getObject()));
        return;
    }

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

    // שומרים על אותו X, מיישרים ל־Y, במרחק attackRange מהיריב
    float dx = playerPos.x - targetPos.x;
    float sign = (dx >= 0) ? -1.f : 1.f; // איזה צד של המותקף?
    // float alignedX = targetPos.x + sign * 80.f; --> MAKING PROBLEM OF ATTACK AMINATION TO THE WRONG SIDE
    float alignedY = targetPos.y; // יישור מדויק, או בתוך טולרנס קטן

    player.setPosition({ playerPos.x, alignedY }); // suppose to be alignedX
}

void AttackingState::name() {
    std::cout << "AttackingState" << std::endl;
}