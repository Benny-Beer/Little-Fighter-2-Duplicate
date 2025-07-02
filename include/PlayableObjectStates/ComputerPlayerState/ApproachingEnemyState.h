#pragma once

#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"
#include <memory>

class PlayableObject;

class ApproachingEnemyState : public ComputerPlayerState {
public:
    explicit ApproachingEnemyState(PlayableObject* target);

    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override;
    void onStoneHit(PlayableObject& player) override {};
    void onExplosion(PlayableObject& player) override {};

private:
    PlayableObject* m_target; // the enemy we approaching
};
