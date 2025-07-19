#include "Objects/Weapons/Rock.h"
#include "EventCommands/StoneHitCommand.h"

Rock::Rock(const sf::Vector2f pos, const std::string& name)
    :BigWeapon(pos, name, std::make_unique<StoneHitCommand>())
{
	std::cout << "in Rock constructor\n";
    std::cout << name << '\n';
    setAnimation(AnimationManager::getAnimation(name, getTexture()));

    
}

void Rock::update(float dt)
{
    /*if (!m_command)
    {
        m_command = std::make_unique<StoneHitCommand>();
    }*/
    BigWeapon::update(dt);
    if (m_isFlying)
    {
        std::cout << "\n\n in m_isFlying condition\n\n";

        // עדכון מיקום:
        sf::Vector2f pos = getPosition();
        std::cout << "Y is:" << pos.y << "\n";
        pos.x += m_velocity.x * dt;
        pos.y += m_velocity.y * dt;

        // òãëåï îäéøåú Y òí Gravity:
        m_velocity.y += m_gravity * dt;
        std::cout << "\n\n\n\n\n\nnow here out of ground y\n\n\n\n\n\n";
        // äàí ðçúðå?
        if (pos.y >= m_groundY - 12.f)
        {
            std::cout << "\n\n\n\n\n\nnow here ground y\n\n\n\n\n\n";
            setHolder(nullptr);
            pos.y = m_groundY;
            m_isFlying = false;  // äôñé÷ ìòåó
            m_velocity = { 0.f, 0.f };
            m_status = ON_EARTH; // Change status to ON_EARTH
            std::cout << "Rock landed!\n";
            setAnimation(AnimationManager::getAnimation("r", getTexture()));


        }
        std::cout << "i was here before\n";
        setPosition(pos);
    }
    if (m_justDropped)
    {
        std::cout << "\n\n in m_justDropped condition\n\n";
        drop(dt);
    }
	

    updateAnimation(dt);
    apllySprite();
}


bool Rock::m_registered = Factory<PickableObject>::registerIt("r", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Rock>(pos, name);
    });