#include "Objects/ObjectStates/IdleObjState.h"
#include "Objects/PickableObject.h"


void IdleObjState::enter(PickableObject& obj)
{
	// Set the object to idle state
	std::cout << "Entering Idle State for object: " << obj.getName() << std::endl;
	obj.setStateName("idle");
}

void IdleObjState::update(PickableObject& obj, float dt)
{
}
