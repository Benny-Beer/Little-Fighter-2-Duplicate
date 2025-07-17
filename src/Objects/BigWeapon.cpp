#include "Objects/BigWeapon.h"


BigWeapon::BigWeapon(const sf::Vector2f pos, const std::string& name, std::unique_ptr<ICommand> cmd)
	:PickableObject(pos, name, std::move(cmd))
{
}

void BigWeapon::update(float dt)
{
    if (!picked()) {
        Object::update(dt);
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

void BigWeapon::throwMe(int direction, float groundY, float speed)
{
    m_xDirThrow = direction;
    m_isFlying = true;
    m_groundY = groundY;

    // מהירות התחלתית:
    m_velocity.x = direction * speed;
    m_velocity.y = -100.f;  // לזרוק קצת למעלה (שלילי כי Y יורד למטה)
    setAnimation(AnimationManager::getAnimation("rock_flying", getTexture()));

    std::cout << "thrown! Velocity x=" << m_velocity.x << " y=" << m_velocity.y << " groundY=" << m_groundY << "\n";
}
