#include "EventCommands/ICommand.h"
#include "Objects/PlayableObject.h"

class StoneHitCommand : public ICommand {
	StoneHitCommand() = default;
	void execute(PlayableObject& player) override;
};