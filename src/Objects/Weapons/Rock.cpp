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
        std::cout << "\n\n in m_isFlying condition\n\n";

        // עדכון מיקום:
        sf::Vector2f pos = getPosition();
        pos.x += m_velocity.x * dt;
        pos.y += m_velocity.y * dt;

        // òãëåï îäéøåú Y òí Gravity:
        m_velocity.y += m_gravity * dt;

        // äàí ðçúðå?
        if (pos.y >= m_groundY)
        {
            std::cout << "now here\n";

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

//need to get the direction and groundY from the player
void Rock::throwRock(int direction, float groundY, float speed)
{
    m_isFlying = true;
    m_groundY = groundY;
    
    // מהירות התחלתית:
    m_velocity.x = direction * speed * 0.5 ;
    m_velocity.y = -400.f;  // לזרוק קצת למעלה (שלילי כי Y יורד למטה)
	setAnimation(AnimationManager::getAnimation("rock_flying", getTexture()));

// }

bool Rock::m_registered = Factory<PickableObject>::registerIt("r", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Rock>(pos, name);
    });