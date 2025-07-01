#include "Objects/ObjectStates/IdleObjState.h"
#include "Objects/PickableObject.h"


void IdleObjState::enter(PickableObject& obj)
{
	obj.setStateName("idle");
}

void IdleObjState::update(PickableObject& obj, float dt)
{
}
