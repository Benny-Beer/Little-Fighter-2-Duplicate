#pragma once
class PlayableObject;

class  ICommand {
public:
	virtual ~ICommand() = default;
	virtual void execute(PlayableObject& player) = 0;
};