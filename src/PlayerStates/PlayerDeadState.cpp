#include "PlayableObjectStates/PlayerStates/PlayerDeadState.h"
#include "Objects/PlayableObject.h"

std::unique_ptr<PlayableObjectState> PlayerDeadState::handleInput(Input input)
{
	return nullptr;
}

void PlayerDeadState::enter(PlayableObject& player)
{
	std::cout << player.getName() << ": im dead now\n";
	player.setAniName("dead");
	player.resetDirection();
}
