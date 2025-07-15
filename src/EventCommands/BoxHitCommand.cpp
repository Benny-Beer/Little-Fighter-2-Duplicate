#include "EventCommands\BoxHitCommand.h"

void BoxHitCommand::execute(PlayableObject& player)
{
	player.reduceHp(30);
	player.onBoxHit();
}
