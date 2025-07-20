#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/RetreatingState.h"


BlockingState::BlockingState() = default;

void BlockingState::enter(PlayableObject& player) {
    player.dropHeldObj();

    player.setAniName("blocking");
    //player.setDiraction(m_input); 
    m_elapsedTime = 0.0f;
    // need information that the player is now blocking - ?

}

void BlockingState::update(PlayableObject& player, float deltaTime) {

    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_blockDuration) {
        // need information that the player is no longer blocking - ?
        player.setState(std::make_unique<RetreatingState>());
    }
}

void BlockingState::exit(ComputerPlayer& player) {
    player.setBlocking(false); // Ensure cleanup even if exited early
}

void BlockingState::name() {
}
void BlockingState::onHandsAttack(PlayableObject& player) {
   
}

void BlockingState::onStoneHit(PlayableObject& player) {

}
void BlockingState::onBoxHit(PlayableObject& player)
{
}
void BlockingState::onExplosion(PlayableObject& player) {

}
