#pragma once
#include "Screens/IScreen.h"
#include "Screens/InGameScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"
#include "Management/GameManager.h"
#include "Gameplaye/Player.h"
#include "Management/ResourceManager.h"

#include <iostream>
#include <stdexcept>
#include <memory>

InGameScreen::InGameScreen(sf::RenderWindow& window, GameManager& manager, PlayerData p) : IScreen(window, manager)																			
{
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::shared_ptr<Ally>> allies;
	players.push_back(std::make_shared<Player>(p));
	Controller m_controller(window, std::make_unique<Level>("lvl1bg", sf::Vector2f(m_window.getSize())),players ,allies);
}



void InGameScreen::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
    //m_level.update(dt);
	//m_player.update(dt);
//	m_level.handleCollisionsWithPlayer(m_player);
	m_controller.updateWorld(dt); // for later. dont let it stay hard coded
    
   

    /*player.handleInput(RELEASE_RIGHT);
    player.handleInput(PRESS_LEFT);*/
    // ????

}

void InGameScreen::handleEvents(sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased )
	{
		m_controller.handleInput(ev);
		//m_player.handleInput(ev);
		//if (ev.mouseButton.button == sf::Mouse::Button::Left) {
		//	auto mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);
		//	if (m_startButton.isClicked(mousePos)) {
		//		m_manager.switchState(std::make_unique<InGameState>(m_window, m_manager));
		//	}
		//}
	}
}

void InGameScreen::render() {

	//m_backGround->draw(m_window, sf::RenderStates::Default);
	//m_startButton.draw(m_window, sf::RenderStates::Default);
    //m_window.clear();
	m_controller.render();
    //m_level.render(m_window);
	//m_player.draw(m_window);
    //m_window.display();
}