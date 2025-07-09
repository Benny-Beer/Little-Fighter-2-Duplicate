#include "Objects/PlayableObject.h"
#include "Objects/PickableObject.h"


void PlayableObject::setState(std::unique_ptr<PlayableObjectState> newState)
{
    m_state = std::move(newState);
    m_state->enter(*this);
}

void PlayableObject::handleCommand(std::unique_ptr<ICommand> command)
{
    command->execute(*this);
}

void PlayableObject::pickUpObject(std::shared_ptr<PickableObject> obj)
{
    m_heldObject = obj;

    //just for expirience. must do it nice
    m_strategyName = obj->getName();
    auto attack = Factory<AttackBehavior>::createAttackBehavior(m_strategyName, m_heldObject, this);
    if (attack)
    {
        m_attack = std::move(attack);
    }
}

void PlayableObject::setDiraction(Input input)
{
    switch (input)
    {
    case PRESS_LEFT:
        m_direction.x = -1.f;
        m_dir = Direction::LEFT;
        setScale(-1);
        break;
    case PRESS_RIGHT:
        m_direction.x = 1.f;
        m_dir = Direction::RIGHT;
        setScale(1);
        break;
    case RELEASE_LEFT:
    case RELEASE_RIGHT:
        m_direction.x = 0.f;
        break;
    case PRESS_JUMP:
    case PRESS_UP:
        m_direction.y = -1.f;
        break;
    case PRESS_FALLING:
    case RELEASE_UP:
    case RELEASE_DOWN:
        m_direction.y = 0.f;
        break;
    case PRESS_DOWN:
        m_direction.y = 1.f;
        break;
    default:
        break;
    }
}

void PlayableObject::attack()
{

    if (m_attack)
    {
        m_attack->attack();
    }
    
    if (m_heldObject)
    {
        m_heldObject->throwIt();
        m_heldObject = nullptr;

        m_attack = Factory<AttackBehavior>::createAttackBehavior("h", nullptr, this);
    }


}

std::shared_ptr<PickableObject> PlayableObject::getHeldObj() const
{
    return m_heldObject;
}

void PlayableObject::dropHeldObj() {
    m_heldObject = nullptr;
}

void PlayableObject::setStrategyName(const std::string& name)
{
    m_strategyName = name;
}

void PlayableObject::takeDamage(int damageAmount) {
  /*  // Reduce health
    m_health -= damageAmount;

    // Clamp health to non-negative
    if (m_health < 0)
        m_health = 0;

    // Optionally: play a hurt animation or effect
    setAnimation("Hurt");

    // Optionally: apply knockback or visual feedback
    applyKnockback();

    // Check for death
    if (m_health == 0)
        onDeath(); */
}

void PlayableObject::resetDirection()
{
    if (m_direction.x != 0 || m_direction.y != 0)
    {
        m_direction = { 0.f, 0.f };
    }
}

void PlayableObject::updateScale()
{
    sf::Vector2f pos = getPosition();
    float dx = pos.x - m_prevPosition.x;


    if (dx > 0.01f)
        setScale(1);  // moving right
    else if (dx < -0.01f)
        setScale(-1); // moving left


    //int dir = static_cast<int>(m_dir);
    //dir *= -1;
    //m_dir = static_cast<Direction>(dir);
}

float PlayableObject::getSpeed() const
{
    return m_speed;
}

void PlayableObject::move(const sf::Vector2f& delta) {
    getSprite().move(delta);
    if (m_heldObject)
    {
        m_heldObject->move(getPosition());
    }
}

void PlayableObject::move(float dt)
{
    m_prevPosition = getPosition();

    sf::Vector2f velocity = m_direction;

    // Normalize diagonal movement (to prevent faster diagonal movement)
    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        constexpr float invSqrt2 = 0.70710678118f;
        velocity.x *= invSqrt2;
        velocity.y *= invSqrt2;
    }

    // Apply speed and delta time
    sf::Vector2f delta(velocity.x * m_speed * dt,
        velocity.y * m_speed * dt);
    moveSprite(delta);
    if (m_heldObject)
    {
        m_heldObject->move(getPosition());
    }

}

void PlayableObject::setAniName(const std::string& name)
{
    m_aniName = name;
}

std::string PlayableObject::getName() const
{
    return m_name;
}

//bool PlayableObject::isAttacked() const
//{
//    return m_underAttack;
//}

//void PlayableObject::attack()
//{
//    m_underAttack = true;
//}

void PlayableObject::tookItem()
{
    m_needItem = false;
}
void PlayableObject::wantItem()
{
    m_needItem = true;
}


bool PlayableObject::needItem()
{
    return m_needItem;
}

void PlayableObject::adjustRange(float range)
{
    m_attackRange = range;
}

float PlayableObject::getAttackRange() const
{
    return m_attackRange;
}

std::string PlayableObject::getStrategyName() {
    return m_strategyName;
}