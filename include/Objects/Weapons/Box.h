#pragma once
#include "Objects/BigWeapon.h"

class Box : public BigWeapon
{
public:
	Box(const sf::Vector2f pos, const std::string& name);
	virtual void playAttack() override {};
private:
	static bool m_registered;
};