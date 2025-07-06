#include "Attacks/RockAttack.h"
#include "Factory/Factory.h"
#include "Objects/Weapons/Rock.h"
#include "Gameplay/Player.h"



RockAttack::RockAttack(const std::string& name, std::shared_ptr<PickableObject> obj)
    :m_rock(obj)
{
    std::cout << " creating attack\n";
}

RockAttack::RockAttack(const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player)
	:m_player(player), m_rock(obj)
{
	std::cout << " creating attack with player\n";

}

void RockAttack::attack()
{
    std::cout << "in RockAttack::attack\n";
    if (m_rock)
    {

		m_rock->playAttack();
        std::cout << "                                            " << m_player->getDirection() << std::endl;
		dynamic_cast<Rock*>(m_rock.get())->throwRock(m_player->getDirection(), m_player->getPosition().y);
		//m_rock->playAttack();
		m_rock = nullptr; 
    } 
}



bool RockAttack::m_register = Factory<AttackBehavior>::registerAttackBehavior("r",
    [](const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player) {
        return std::make_unique<RockAttack>(name, obj, player);
    });




