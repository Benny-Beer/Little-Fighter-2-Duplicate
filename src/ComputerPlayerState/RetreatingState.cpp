#include "PlayableObjectStates/ComputerPlayerState/RetreatingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include <SFML/System/Vector2.hpp>

RetreatingState::RetreatingState() = default;

void RetreatingState::enter(PlayableObject& player) {
    std::cout << "enter:: RetreatingState\n";
    player.dropHeldObj();

    //Animation retreatingAnim(player.getTexture(),
    //    0, 0,          // x, y
    //    80, 80,        // width, height
    //    4,             // מספר פריימים
    //    0.2f);         // זמן בין פריימים

    //player.setAnimation(retreatingAnim);
    player.setAniName("running");
    m_safeZone = player.getSafeZone();

    //player.setDiraction(m_input);     m_elapsedTime = 0.f;
}

void RetreatingState::update(PlayableObject& player, float deltaTime) {
    m_elapsedTime += deltaTime;

    // Move away from nearest visible threat (for now just move left/up)
    // You can enhance this to analyze real threats nearby
    
    sf::Vector2f retreatDirection = m_safeZone - player.getPosition();
    float length = std::sqrt(retreatDirection.x * retreatDirection.x + retreatDirection.y * retreatDirection.y);
    if (length != 0) {
        retreatDirection /= length;
        retreatDirection *= 3.f;
    }
    player.move(retreatDirection * player.getSpeed() * deltaTime);

    if (m_elapsedTime >= m_retreatDuration) {
        // Done retreating — return to idle (or other smart decision)
        player.setState(std::make_unique<IdleState>());
        return;
    }
}

void RetreatingState::exit(ComputerPlayer& player) {
    // Cleanup if needed
}

void RetreatingState::onHandsAttack(PlayableObject& player) {

}

void RetreatingState::onStoneHit(PlayableObject& player) {

}
void RetreatingState::onExplosion(PlayableObject& player) {

}