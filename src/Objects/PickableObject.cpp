#include "Objects/PickableObject.h"
#include "Objects/ObjectStates/IdleObjState.h"


PickableObject::PickableObject(const sf::Vector2f pos, const std::string& name)
	:Object(pos, name), m_name(name), m_state(std::make_unique<IdleObjState>())
{

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

void PickableObject::setState(std::unique_ptr<ObjectBaseState> state)
{
	m_state = std::move(state);
	if (m_state) {
		m_state->enter(*this);
	}
}
