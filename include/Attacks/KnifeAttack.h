#pragma once
#include "Attacks/AttackBehavior.h"
#include "Objects/Weapons/Knife.h"

class PlayableObject;

class KnifeAttack : public AttackBehavior {
public:
	KnifeAttack(const std::string& name, PickableObject* obj);
	KnifeAttack(const std::string& name, PickableObject* obj, PlayableObject* player);
	virtual void attack() override;
private:
	PlayableObject* m_player = nullptr;
	PickableObject* m_knife = nullptr;
	static bool m_register;

};
