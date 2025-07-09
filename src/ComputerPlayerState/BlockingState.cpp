#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/RetreatingState.h"


BlockingState::BlockingState() = default;

void BlockingState::enter(PlayableObject& player) {
    std::cout << "enter:: BlockingState\n";

    Animation blockingAnim(player.getTexture(),
        480, 400,          // x, y
        80, 80,        // width, height
        2,             // מספר פריימים
        0.2f);         // זמן בין פריימים

    player.setAnimation(blockingAnim);
    //player.setDiraction(m_input); 
    m_elapsedTime = 0.0f;
    // need information that the player is now blocking - ?

}

void BlockingState::update(PlayableObject& player, float deltaTime) {
    std::cout << player.getName() << "in BlockingState\n";

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
    std::cout << "BlockingState" << std::endl;
}
