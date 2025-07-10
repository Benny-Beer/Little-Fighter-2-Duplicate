#include "Objects/Weapons/Rock.h"
#include "EventCommands/StoneHitCommand.h"

Rock::Rock(const sf::Vector2f pos, const std::string& name)
    :BigWeapon(pos, name, std::make_unique<StoneHitCommand>())
{
    m_range = 100.f;
	std::cout << "in Rock constructor\n";
    std::cout << name << '\n';
    setAnimation(AnimationManager::getAnimation(name, getTexture()));
    
}

void Rock::update(float dt)
{
    if (!m_command)
    {
        m_command = std::make_unique<StoneHitCommand>();
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
            m_status = ON_EARTH; // Change status to ON_EARTH
            std::cout << "Rock landed!\n";
            setAnimation(AnimationManager::getAnimation("r", getTexture()));


        }

        setPosition(pos);
    }
    updateAnimation(dt);
    apllySprite();
}

bool Rock::m_registered = Factory<PickableObject>::registerIt("r", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Rock>(pos, name);
    });