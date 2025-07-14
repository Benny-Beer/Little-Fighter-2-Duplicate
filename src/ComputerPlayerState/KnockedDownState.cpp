#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"
#include "GamePlay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"

KnockedDownState::KnockedDownState() = default;

void KnockedDownState::enter(PlayableObject& player) {
    std::cout << "enter:: KnockedDownState\n";
    player.dropHeldObj();

    //Animation knockedDownAnim(player.getTexture(),
    //    240, 0,          // x, y
    //    80, 80,        // width, height
    //    5,             // מספר פריימים
    //    0.2f,
    //    false);         
    //player.setAnimation(knockedDownAnim);
    player.setAniName("knocked");
    //player.setDiraction(m_input);     
    m_elapsedTime = 0.0f;
    // need information that the player isnt controllable - ?
}

void KnockedDownState::update(PlayableObject& player, float deltaTime) {

    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_recoveryTime) {
        // need information that the player is controllable again - ?
        player.setState(std::make_unique<IdleState>());
    }
}

void KnockedDownState::exit(ComputerPlayer& player) {
    player.setControllable(true); // Restore control in any case
}

void KnockedDownState::onHandsAttack(PlayableObject& player) {

}

void KnockedDownState::onStoneHit(PlayableObject& player) {

}
void KnockedDownState::onExplosion(PlayableObject& player) {

}