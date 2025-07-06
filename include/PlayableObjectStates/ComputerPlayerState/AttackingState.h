#pragma once

#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"
#include <memory>

class PlayableObject;

class AttackingState : public ComputerPlayerState {
public:
    explicit AttackingState(PlayableObject* target);

    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override {};
    void onStoneHit(PlayableObject& player) override {};
    void onExplosion(PlayableObject& player) override {};
    void name();
private:
    PlayableObject* m_target; // the target for attacking
    float m_attackCooldown = 0.f; // time betweeen attacks
    void alignAttacker(PlayableObject& player);
};
