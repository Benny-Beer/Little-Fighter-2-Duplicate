#include "PlayableObjectStates/PlayerStates/AttackState.h"
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "EventCommands/HandsAttackCommand.h"
#include "GamePlay/Player.h"
#include <iostream>


std::unique_ptr<PlayableObjectState> AttackState::handleInput(Input input)
{
    switch (input)
    {

    case END_ATTACK:
        return std::make_unique<StandingState>(input);
        break;
	case PRESS_ATTACK:
		return nullptr;
		break;

    default:
        break;
    }
	return nullptr; 
}

void AttackState::enter(PlayableObject& player)
{
    std::cout << "enter:: AttackState Player\n";
    
    player.setAniName("attacking");
    std::cout << "after setAniName\n";
    player.attack();
    //player.handleCommand(std::make_unique<HandsAttackCommand>());
    std::cout << "after attack()\n";
}

void AttackState::update(PlayableObject& player, float dt)
{
    if (m_clock.getElapsedTime().asSeconds() >= m_attackDuration)
    {
        player.setStrategyName("");
        player.setState(std::make_unique<StandingState>(Input::NONE));
    }
}
