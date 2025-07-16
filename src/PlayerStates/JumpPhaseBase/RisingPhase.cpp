// RisingPhase.cpp
#include "PlayableObjectStates/PlayerStates/JumpBasePhase/RisingPhase.h"
#include "PlayableObjectStates/PlayerStates/JumpBasePhase/HangingPhase.h"
#include "GamePlay/Player.h"

RisingPhase::RisingPhase(float duration, float speed, float groundY)
    : m_duration(duration), m_speed(speed), m_groundY(groundY) {
    m_clock.restart();
}

std::unique_ptr<JumpPhaseBase> RisingPhase::update(PlayableObject& player, float dt) {
    /*auto pos = player.getPosition();
    pos.y -= m_speed * dt;
    player.setPosition(pos);*/
    player.adjustBoundsToJump();
    player.setDiraction(Input::PRESS_JUMP);
    player.move(dt);
    if (m_clock.getElapsedTime().asSeconds() >= m_duration)
    {
        std::cout << "in Jumping::update, m_clock.getElapsedTime().asSeconds() >= m_duration\n";
        return std::make_unique<HangingPhase>(0.2f, m_groundY);


    }

    return nullptr;
}