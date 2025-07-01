#include "Objects/Weapons/Box.h"

Box::Box(const sf::Vector2f pos, const std::string& name)
	:BigWeapon(pos, name)
{
	std::cout << "in Box constructor\n";
	std::cout << name << '\n';
	setAnimation(AnimationManager::getAnimation(name, getTexture()));
	sf::Vector2f offset(10.f, -35.f);
	m_offset = offset;
}

bool Box::m_registered = Factory<PickableObject>::registerIt("b", [](const sf::Vector2f& pos, const std::string& name) {
	return std::make_unique<Box>(pos, name);
	});
