#pragma once

#include "Objects/ObjectStates/ObjectBaseState.h"

class HeldObjState : public ObjectBaseState {

public:
    void enter(PickableObject& objobj) override;
    void update(PickableObject& obj, float dt) override;
};