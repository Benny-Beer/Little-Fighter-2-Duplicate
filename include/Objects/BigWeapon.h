#pragma once
#include "objects/PickableObject.h"

class BigWeapon : public PickableObject {
public:
	BigWeapon(const sf::Vector2f pos, const std::string& name, std::unique_ptr<ICommand> cmd);
	virtual void update(float dt) override;
	void throwMe(int direction, float groundY, float speed = 700.f);
protected:
	bool m_isFlying = false;
	sf::Vector2f m_velocity = { 0.f, 0.f };
	float m_groundY = 0.f;
	float m_gravity = 1000.f;
	
};