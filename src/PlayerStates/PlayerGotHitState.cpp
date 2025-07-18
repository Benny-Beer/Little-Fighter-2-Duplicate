#include "PlayableObjectStates/PlayerStates/PlayerGotHitState.h"
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "Objects/PlayableObject.h"

PlayerGotHitState::PlayerGotHitState(Input input)
{
	m_input = input;
}

std::unique_ptr<PlayableObjectState> PlayerGotHitState::handleInput(Input input)
{
	return nullptr;
}

void PlayerGotHitState::update(PlayableObject& player, float dt)
{
	m_elapsedTime += dt;

	if (m_elapsedTime >= m_recoveryTime) {
		// need information that the player is controllable again - ?
		player.setState(std::make_unique<StandingState>(Input::NONE));
	}
}

void PlayerGotHitState::enter(PlayableObject& player)
{
	player.dropHeldObj();
	m_elapsedTime = 0.5f;
}
