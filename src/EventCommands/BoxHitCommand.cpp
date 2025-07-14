#include "EventCommands\BoxHitCommand.h"

void BoxHitCommand::execute(PlayableObject& player)
{
}
std::unique_ptr<ICommand> BoxHitCommand::clone() const {
    return std::make_unique<BoxHitCommand>(*this);
};
