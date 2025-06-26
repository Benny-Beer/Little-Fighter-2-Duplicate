#pragma once
#include "Objects/Object.h"


class PickableObject : public Object {
public:
	PickableObject(const sf::Vector2f pos, const std::string& name);
	virtual void handleCollision() {};
	const std::string& getName();
	virtual void move(sf::Vector2f goal);
	virtual void playAttack() = 0;
	const std::string& getStateName() const { return m_state; }
	virtual void setStateName(const std::string& state) { m_state = state; }
protected:
	sf::Vector2f m_offset;
private:
	sf::Vector2f m_goalPosition;
	std::string m_name;
	std::string m_state = "idle"; // Default state is idle
	std::string m_animationName; // Default animation name is idle
};
