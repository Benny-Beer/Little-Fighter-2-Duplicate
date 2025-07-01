#pragma once
#include "Objects/Object.h"
#include "Objects/ObjectStates/ObjectBaseState.h"
#include "Objects/PlayableObject.h"
#include <memory>


class PickableObject : public Object {
public:
	PickableObject(const sf::Vector2f pos, const std::string& name);
	virtual void handleCollision() {};
	const std::string& getName();
	virtual void move(sf::Vector2f goal);
	virtual void playAttack() = 0;


	void setHolder(PlayableObject* holder); 
	PlayableObject* getHolder() const;
	const std::string& getStateName() const { return m_stateName; }
	void setStateName(const std::string& state) { m_stateName = state; }
	void setAnimationName(const std::string& animationName) { m_animationName = animationName; }
	const std::string& getAnimationName() const { return m_animationName; }
	void setState(std::unique_ptr<ObjectBaseState> state);
protected:
	sf::Vector2f m_offset;
private:
	std::unique_ptr<ObjectBaseState> m_state;
	PlayableObject* m_holder = nullptr;

	sf::Vector2f m_goalPosition;
	std::string m_name;
	std::string m_stateName ; // Default state is idle
	std::string m_animationName; // Default animation name is idle
};
