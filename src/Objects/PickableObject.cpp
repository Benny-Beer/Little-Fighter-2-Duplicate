#include "Objects/PickableObject.h"
#include "Objects/ObjectStates/IdleObjState.h"


PickableObject::PickableObject(const sf::Vector2f pos, const std::string& name, std::unique_ptr<ICommand> cmd)
	:Object(pos, name), m_name(name), m_command(std::move(cmd)), m_range(250.f)
{
	sf::Vector2f offset(2.f, -62.f);
	m_offset = offset;
}

const std::string& PickableObject::getName()
{
	return m_name;
}

void PickableObject::move(sf::Vector2f goal)
{
	m_goalPosition = goal;
	setPosition(m_goalPosition + m_offset);
	
	
}

std::unique_ptr<ICommand> PickableObject::getHitCommand()
{
	 std::cout << "PickableObject::getHitCommand() called\n";
	 std::cout << getName() << std::endl;
	 std::cout << "command name is: " << typeid(*m_command).name() << std::endl;
	 return std::move(m_command->clone());
}

void PickableObject::markAsUsed()
{
	m_used = true;
}

bool PickableObject::isUsed() const
{
	return m_used;
}

void PickableObject::setHolder(PlayableObject* holder)
{
	m_holder = holder;
}

PlayableObject* PickableObject::getHolder() const
{
	return m_holder;
}

void PickableObject::setState(std::unique_ptr<ObjectBaseState> state)
{
	m_state = std::move(state);
	if (m_state) {
		m_state->enter(*this);
	}
}

const int PickableObject::getXDirThrow() const
{
	return m_xDirThrow; 
}

void PickableObject::putBack()
{
    m_status = ON_EARTH;
    m_justDropped = true;
    m_dropTarget = getPosition() - (m_offset + m_offset);
}

//void PickableObject::drop(float dt)
//{
//    // 1. חישוב יעד
//    std::cout << "\n\nin PickableObject::drop\n\n";
//
//    sf::Vector2f target = getPosition() - m_offset;
//    std::cout << target.x << "," << target.y << std::endl;
//    // 2. חישוב וקטור תזוזה (נורמליזציה)
//    sf::Vector2f dir = target - getPosition();
//    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//    
//    // הגדרת מהירות קבועה (פיקסלים לשנייה)
//    const float SPEED = 80.f;
//    float moveDist = SPEED * dt;
//
//    if (distance <= moveDist || distance == 0.f) {
//        // הגעת ליעד או עברת אותו — מעדכן למיקום הסופי ומפעיל אנימציה
//        setPosition(target);
//        m_justDropped = false;
//        //playHitGroundAnimation();
//    }
//    else {
//        // תזוזה רגילה לעבר היעד
//        std::cout << "\n\nin else condition\n\n";
//
//        sf::Vector2f step = dir / distance * moveDist;
//        setPosition(getPosition() + step);
//    }
//    apllySprite();
//    
//}

void PickableObject::drop(float dt)
{
    sf::Vector2f dir = m_dropTarget - getPosition();
    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    const float SPEED = 400.f;
    float moveDist = SPEED * dt;

    if (distance <= moveDist || distance == 0.f) {
        // מזיז ישר ליעד וסוגר תנועה
        setPosition(m_dropTarget);
        m_justDropped = false;
        //playHitGroundAnimation();
    }
    else {
        // תנועה רגילה
        sf::Vector2f step = dir / distance * moveDist;
        setPosition(getPosition() + step);
    }
}
