#pragma once
#include "Gameplay/Enemy.h"
#include "Consts/Consts.h"

class Bandit : public Enemy {
public:
	Bandit(const sf::Vector2f pos);
	virtual void handleCollision() override;
	//virtual void update(/*float dt*/ const sf::Vector2f playerPos) override;
	//void move(const sf::Vector2f playerPos);
private:
	static bool m_registered;

	//used in move()
	sf::Vector2f m_direction{ 0.f,0.f };
	float m_attackRange = HANDS_ATTACK_RANGE;
};