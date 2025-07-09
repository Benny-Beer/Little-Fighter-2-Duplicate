//#include "Objects/Weapons/Knife.h"
//#include "Objects/ObjectStates/IdleObjState.h"
//
//Knife::Knife(const sf::Vector2f pos, const std::string& name)
//	:SmallWeapon(pos, name)
//{
//	setState(std::make_unique<IdleObjState>());
//	m_offset = sf::Vector2f(13.f, 24.f); // Adjust the offset as needed
//	setSize(1.1f);
//	std::cout << getStateName() << '\n';	
//	setAnimation(AnimationManager::getAnimation(getStateName(), getTexture()));
//}
//
//void Knife::playAttack()
//{
//	std::cout << "in Knife attack playattack\n";
//}
//
//void Knife::update(float dt)
//{
//	if (getAnimationName() != /*getName() +*/ getStateName())
//	{
//		setAnimationName(/*getName() +*/ getStateName());
//		setAnimation(AnimationManager::getAnimation(getAnimationName(), getTexture()));
//	}
//	updateAnimation(dt);
//	apllySprite();
//	
//}
//
//
//
//bool Knife::m_registered = Factory<PickableObject>::registerIt("k", [](const sf::Vector2f& pos, const std::string& name) {
//	return std::make_unique<Knife>(pos, name);
//	});
