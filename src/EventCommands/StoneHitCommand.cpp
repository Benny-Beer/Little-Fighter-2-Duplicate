#include "EventCommands/StoneHitCommand.h"

void StoneHitCommand::execute(PlayableObject& player)
{
	//player.setAniName("stonehit");
	player.reduceHp(60); 
	player.onStoneHit();
	std::cout << typeid(player).name() << "ON STONE HIT!!!!!!!!!!!!!\n";
	// player.takeDamage(40); // for example... 
	// add anything else that happens when player hit by stone
}

std::unique_ptr<ICommand> StoneHitCommand::clone() const {
	return std::make_unique<StoneHitCommand>(*this);
};
