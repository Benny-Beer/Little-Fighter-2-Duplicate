#pragma once

#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"
#include <memory>

class PickableObject;

class PickingUpItemState : public ComputerPlayerState {
public:
    explicit PickingUpItemState(std::shared_ptr<PickableObject> item);

    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override {};
    void onStoneHit(PlayableObject& player) override {};
    void onExplosion(PlayableObject& player) override {};

private:
    std::shared_ptr<PickableObject> m_targetItem;
};
