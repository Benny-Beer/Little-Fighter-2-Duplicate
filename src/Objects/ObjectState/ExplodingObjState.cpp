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
	if (m_clock.getElapsedTime().asSeconds() > m_explosionDuration) {
		std::cout << "ExplodingObjState::update - time to destroy\n";
		obj.markAsUsed();
		obj.setState(nullptr); // Change state to HeldObjState
		std::cout << "ExplodingObjState::update - object marked as used\n";
	}
}


