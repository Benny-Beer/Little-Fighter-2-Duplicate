#include "Objects/Weapons/Box.h"
#include "Objects/ObjectStates/ExplodingObjState.h"
#include "EventCommands/BoxHitCommand.h"

Box::Box(const sf::Vector2f pos, const std::string& name)
	:BigWeapon(pos, name, std::make_unique<BoxHitCommand>())
{
	std::cout << "in Box constructor\n";
	std::cout << name << '\n';
	setAnimation(AnimationManager::getAnimation(name, getTexture()));
	
}

void Box::update(float dt)
{
    Object::update(dt);
    if (!m_command)
    {
		m_command = std::make_unique<BoxHitCommand>();
    }
    if (m_isFlying)
    {
        // עדכון מיקום:
        sf::Vector2f pos = getPosition();
        pos.x += m_velocity.x * dt;
        pos.y += m_velocity.y * dt;

        // עדכון מהירות Y עם Gravity:
        m_velocity.y += m_gravity * dt;

        // האם נחתנו?
        if (pos.y >= m_groundY)
        {
            pos.y = m_groundY;
            m_isFlying = false;  // הפסיק לעוף
            m_velocity = { 0.f, 0.f };
            std::cout << "Rock landed!\n";
            //setAnimation(AnimationManager::getAnimation("r", getTexture()));
			setState(std::make_unique<ExplodingObjState>()); // Change state to ExplodingObjState
            
        }

        setPosition(pos);
    }
    if (getState())
    {
        std::cout << "Box state is not null\n";
        getState()->update(*this, dt);
    }

    updateAnimation(dt);
    apllySprite();
}



bool Box::m_registered = Factory<PickableObject>::registerIt("b", [](const sf::Vector2f& pos, const std::string& name) {
	return std::make_unique<Box>(pos, name);
	});
