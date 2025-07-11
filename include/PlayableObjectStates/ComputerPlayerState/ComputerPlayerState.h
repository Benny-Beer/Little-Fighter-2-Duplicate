#pragma once
#include "PlayableObjectStates/PlayableObjectState.h"

class ComputerPlayer;

class ComputerPlayerState : public PlayableObjectState {
public:
    virtual ~ComputerPlayerState() = default;
    std::unique_ptr<PlayableObjectState> handleInput(Input input) { return nullptr; };

    //virtual void enter(ComputerPlayer& player) = 0;
    //virtual void update(ComputerPlayer& player, float deltaTime) = 0;
    virtual void exit(ComputerPlayer& player) = 0;
};
