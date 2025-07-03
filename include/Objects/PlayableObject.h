#pragma once
#include "Objects/Object.h"
#include "PlayableObjectStates/PlayableObjectState.h"
#include "EventCommands/ICommand.h"

enum class Direction
{
	RIGHT = 1, LEFT = -1
};


class PlayableObject : public Object{
public:
	PlayableObject(sf::Vector2f pos, const std::string& name) : Object(pos, name), m_prevPosition(pos) {}
	void setState(std::unique_ptr<PlayableObjectState> newState); 
	virtual void handleCommand(std::unique_ptr<ICommand> command);
	virtual void pickUpObject(std::shared_ptr<PickableObject> obj);
	virtual void setDiraction(Input input);
	virtual void attack();
	virtual int getDirection() const { return static_cast<int>(m_dir); }
	virtual void setStrategyName(const std::string& name);


	virtual void takeDamage(int damageAmount);
	virtual void update(float dt) = 0;
	virtual float getSpeed() const;
	virtual void move(const sf::Vector2f& delta);
	virtual void move(float dt);
	virtual void setAniName(const std::string& name);
	virtual std::string getName() const;
	virtual void updateScale();
	virtual PlayableObject* getTarget() { return nullptr; };
	virtual std::shared_ptr<PickableObject> getObject() { return nullptr; };

	//virtual bool isAttacked() const;
	//virtual void attack();
	virtual void tookItem();
	virtual bool needItem();

	// in-game Events:
	virtual void onHandsAttack() { m_state->onHandsAttack(*this); }



protected:
	int m_hp;
	int m_energy;
	float m_speed;
	std::string m_aniName;
	std::string m_strategyName = "";
	std::string m_currentAnimationName;
	std::string m_name;
	sf::Vector2f m_prevPosition;
	//bool m_underAttack = false;
	bool m_needItem = true;
	std::unique_ptr<PlayableObjectState> m_state;
	std::unique_ptr<AttackBehavior> m_attack;
	std::shared_ptr<PickableObject> m_heldObject = nullptr;
	Direction m_dir = Direction::RIGHT;
	sf::Vector2f m_direction{ 0.f,0.f };

};
