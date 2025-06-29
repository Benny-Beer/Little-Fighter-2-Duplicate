#pragma once
#include "Objects/ObjectStates/ObjectBaseState.h"

class WalkingObjState : public ObjectBaseState {
public:
	void enter(PickableObject& obj) override;
	void update(PickableObject& obj,float dt) override;
};