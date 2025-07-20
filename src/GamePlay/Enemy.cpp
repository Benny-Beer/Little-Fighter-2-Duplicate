#include "GamePlay/Enemy.h"
#include "Management/AnimationManager.h"


Enemy::Enemy(const sf::Vector2f pos, const std::string& name, float speed)
    : ComputerPlayer(pos, name)
{
    resetHP();
    m_speed = speed;
    // Starts with IdleState
    changeState(std::make_unique<IdleState>());
    m_name = "enemy";

}



void Enemy::update(float dt)
{

    //m_prevPosition = getPosition();

    ComputerPlayer::update(dt);  // æä îôòéì àú äÎstate
    //std::cout << "Player Pos is: " << getPosition().x << "," << getPosition().y << "\n";

    if (m_currentAnimationName != m_aniName + m_strategyName) {
        setAnimation(AnimationManager::getAnimation(m_aniName + m_strategyName, getTexture()));
        m_currentAnimationName = m_aniName + m_strategyName;
    }
    //std::cout << "my target is: " << m_target->getName() << std::endl;
    updateScale();
    updateAnimation(dt);
    apllySprite();
    //m_prevPosition = getPosition();

}

void Enemy::handleCollision() {
    // òãééï ìà îåâãø îä ÷åøä áäúðâùåú, àæ ðùàéø øé÷ áéðúééí
}




bool Enemy::isAlive() const {
    return m_alive;
}

void Enemy::resetHP() {
    m_hp = 100;
    m_potentialHp = 100;
}

