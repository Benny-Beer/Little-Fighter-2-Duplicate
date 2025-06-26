#include "Objects/Weapons/Rock.h"

Rock::Rock(const sf::Vector2f pos, const std::string& name)
	:BigWeapon(pos, name)
{
	
    setAnimation(AnimationManager::getAnimation(getName(), getTexture()));
    sf::Vector2f offset(10.f, -35.f);
    m_offset = offset;
    
}

bool Rock::m_registered = Factory<PickableObject>::registerIt("r", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Rock>(pos, name);
    });