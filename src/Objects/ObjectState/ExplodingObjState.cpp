#include "objects/ObjectStates/ExplodingObjState.h"

void ExplodingObjState::enter(PickableObject& obj)
{
	std::cout << "ExplodingObjState::enter\n";
	m_clock.restart();
	obj.setAnimation(AnimationManager::getAnimation("boxExploiding", &ResourceManager::instance().getTexture("broken")));
	obj.setSize(2); // Set size for explosion effect
	//sound?
}

void ExplodingObjState::update(PickableObject& obj, float dt)
{
	std::cout << "ExplodingObjState::update\n";
	m_elapsedTime += dt;
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n" << m_elapsedTime <<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
	if (m_elapsedTime > m_explosionDuration) {
		std::cout << "ExplodingObjState::update - time to destroy\n";
		obj.markAsUsed();
		obj.setState(nullptr); // Change state to HeldObjState
		std::cout << "ExplodingObjState::update - object marked as used\n";
	}
}


