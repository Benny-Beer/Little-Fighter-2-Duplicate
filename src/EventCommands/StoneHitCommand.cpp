#include "EventCommands/StoneHitCommand.h"

void StoneHitCommand::execute(PlayableObject& player)
{
	//player.setAniName("stonehit");
	player.onStoneHit();
	std::cout << "ON STONE HIT!!!!!!!!!!!!!\n";
	// player.takeDamage(40); // for example... 
	// add anything else that happens when player hit by stone
}