#pragma once
#include "Attacks/AttackBehavior.h"
#include "Objects/Weapons/Box.h"


class Player;

class BoxAttack : public AttackBehavior {
public:
	BoxAttack(const std::string& name, PickableObject* obj, Player* player);
	virtual void attack() override;
private:
	PickableObject* m_box = nullptr;
	Player* m_player = nullptr;
	static bool m_register;

};
