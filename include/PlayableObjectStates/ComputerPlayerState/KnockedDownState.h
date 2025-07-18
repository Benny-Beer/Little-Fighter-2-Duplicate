#pragma once

#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"

class KnockedDownState : public ComputerPlayerState {
public:
    KnockedDownState();

    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override;
    void onStoneHit(PlayableObject& player) override;
    void onBoxHit(PlayableObject& player) override;
    void onExplosion(PlayableObject& player) override;
    bool isAccessible() const override { return false; }
    void name() {};
private:
    float m_recoveryTime = 1.5f;  // Time lying down before recovery
    float m_elapsedTime = 0.0f;
};
