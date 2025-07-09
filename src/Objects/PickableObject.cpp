#include "Objects/PickableObject.h"
#include "Objects/ObjectStates/IdleObjState.h"


PickableObject::PickableObject(const sf::Vector2f pos, const std::string& name, std::unique_ptr <ICommand> cmd)
	:Object(pos, name), m_name(name), m_command(std::move(cmd))
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
	 return std::move(m_command);
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
