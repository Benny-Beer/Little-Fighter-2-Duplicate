#include "Gameplay/Ally.h"
#include "Gameplay/Player.h"
#include "Management/AnimationManager.h"
#include <iostream>


Ally::Ally(const sf::Vector2f pos, const std::string& name, float speed)
    : ComputerPlayer(pos, name)
{
    resetHP();
    m_speed = speed;
    // Starts with IdleState
    changeState(std::make_unique<IdleState>());
    m_name = "ally";

}

Ally::Ally(PlayerData p) : ComputerPlayer(p)
{
    setPosition(getRandomYPosition(50, 400, 780));
    m_prevPosition = getPosition();
    m_hp = p.m_hp;
    m_potentialHp = p.m_hp;
    m_speed = p.m_speed;
    m_name = p.m_name;
    changeState(std::make_unique<IdleState>());
}


void Ally::update(float dt) {

    //m_prevPosition = getPosition();

    ComputerPlayer::update(dt);  // זה מפעיל את ה־state
    if (m_currentAnimationName != m_aniName + m_strategyName) {
        setAnimation(AnimationManager::getAnimation(m_aniName + m_strategyName, getTexture()));
        m_currentAnimationName = m_aniName + m_strategyName;
    }
    updateScale();
    updateAnimation(dt);
    apllySprite();
    //m_prevPosition = getPosition();

}

void Ally::handleCollision() {
    // עדיין לא מוגדר מה קורה בהתנגשות, אז נשאיר ריק בינתיים
}




//Ally::Ally(const sf::Vector2f pos, const std::string& name, float speed)
//    : ComputerPlayer(pos, name)
//{
//    m_speed = speed;
//    // Starts with IdleState
//    changeState(std::make_unique<IdleState>());
//}

bool Ally::isAlive() const {
    return m_alive;
}

void Ally::resetHP() {
    m_hp = 500;
    m_potentialHp = 500;
}
