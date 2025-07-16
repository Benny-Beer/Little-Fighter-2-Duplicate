#include "Objects/Weapons/Box.h"
#include "Objects/ObjectStates/ExplodingObjState.h"
#include "EventCommands/BoxHitCommand.h"
#include "EventCommands/ExplodeCommand.h"

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
    if (isExploded())

    {
		m_command = std::make_unique<ExplodeCommand>();
    }
    if (m_isFlying)
    {
        // òãëåï îé÷åí:
        sf::Vector2f pos = getPosition();
        pos.x += m_velocity.x * dt;
        pos.y += m_velocity.y * dt;

        // òãëåï îäéøåú Y òí Gravity:
        m_velocity.y += m_gravity * dt;

        // äàí ðçúðå?
        if (pos.y >= m_groundY)
        {
			explode(); 
            pos.y = m_groundY;
            m_isFlying = false;  // äôñé÷ ìòåó
            m_velocity = { 0.f, 0.f };
            
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
