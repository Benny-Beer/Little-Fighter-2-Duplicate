#pragma once
#include "Objects/Object.h"

enum Status { ON_EARTH, PICKED, THROWN};

class PickableObject : public Object {
public:
	PickableObject(const sf::Vector2f pos, const std::string& name);
	const std::string& getName();
	virtual void move(sf::Vector2f goal);
	void drop(float dt);
	virtual void playAttack() = 0;
	virtual bool onEarth() { return m_status == ON_EARTH; }
	virtual bool picked() { return m_status == PICKED; }
	virtual bool thrown() { return m_status == THROWN; }
	virtual void putBack(); 
	virtual void pick() { m_status = PICKED; }
	virtual void throwIt() { m_status = THROWN; }
	float getRange() const { return m_range; } ;




protected:
	sf::Vector2f m_offset;
	Status m_status = ON_EARTH;
	float m_range;
	bool m_justDropped = false;
	sf::Vector2f m_dropTarget;

private:
	sf::Vector2f m_goalPosition;
	std::string m_name;

};
