#include "Objects/Weapons/Knife.h"

Knife::Knife(const sf::Vector2f pos, const std::string& name)
	:SmallWeapon(pos, name)
{
	setScale(1.1f);
	setAnimation(AnimationManager::getAnimation(getStateName(), getTexture()));
	
}

void Knife::playAttack()
{
	std::cout << "in Knife attack playattack\n";
}

void Knife::update(float dt)
{
	if (getAnimationName() != getName() + getStateName())
	{
		setAnimationName(getStateName());
		setAnimation(AnimationManager::getAnimation(getAnimationName(), getTexture()));
	}
	updateAnimation(dt);
	apllySprite();
	
}



bool Knife::m_registered = Factory<PickableObject>::registerIt("k", [](const sf::Vector2f& pos, const std::string& name) {
	return std::make_unique<Knife>(pos, name);
	});
