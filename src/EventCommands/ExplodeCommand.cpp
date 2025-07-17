#include "EventCommands\ExplodeCommand.h"

void ExplodeCommand::execute(PlayableObject& player)
{
	player.reduceHp(2);
	player.onExplosion();
}
std::unique_ptr<ICommand> ExplodeCommand::clone() const {
	return std::make_unique<ExplodeCommand>(*this);
};
