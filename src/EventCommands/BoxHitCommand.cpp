#include "EventCommands\BoxHitCommand.h"

void BoxHitCommand::execute(PlayableObject& player)
{
	player.reduceHp(30);
	player.onBoxHit();
}
std::unique_ptr<ICommand> BoxHitCommand::clone() const {
    return std::make_unique<BoxHitCommand>(*this);
};
