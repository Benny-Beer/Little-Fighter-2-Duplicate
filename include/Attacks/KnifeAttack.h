#pragma once
#include "Attacks/AttackBehavior.h"
#include "Objects/Weapons/Knife.h"

class PlayableObject;

class KnifeAttack : public AttackBehavior {
public:
	KnifeAttack(const std::string& name, std::shared_ptr<PickableObject> obj);
	KnifeAttack(const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player);
	virtual void attack() override;
private:
	PlayableObject* m_player = nullptr;
	std::shared_ptr<PickableObject> m_knife = nullptr;
	static bool m_register;

};
