#include "EventCommands/StoneHitCommand.h"

void StoneHitCommand::execute(PlayableObject& player)
{
	player.reduceHp(BIG_WEAPON_DAMAGE); 
	player.onStoneHit();
	std::cout << typeid(player).name() << "ON STONE HIT!!!!!!!!!!!!!\n";
	std::cout << player.getHp() << " HP LEFT\n";
	
}

std::unique_ptr<ICommand> StoneHitCommand::clone() const {
	return std::make_unique<StoneHitCommand>(*this);
};
