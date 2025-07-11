#include "EventCommands/HandsAttackCommand.h"
#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include <memory>

void HandsAttackCommand::execute(PlayableObject& player)
{
	player.reduceHp(30);
	player.onHandsAttack();
}