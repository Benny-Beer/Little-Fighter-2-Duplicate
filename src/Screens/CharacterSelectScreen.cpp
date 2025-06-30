#pragma once
#include "Screens/IScreen.h"
#include "Screens/CharacterSelectScreen.h"
#include "Screens/InGameScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"
#include "Management/GameManager.h"
#include "Management/ResourceManager.h"
#include <iostream>
#include <stdexcept>

CharacterSelectScreen::CharacterSelectScreen(sf::RenderWindow& window, GameManager& manager) : IScreen(window, manager)
{
	sf::Vector2f screenSize(static_cast <sf::Vector2f> (m_window.getSize()));
	m_backGround = Background(screenSize, ResourceManager::instance().getTexture("screen_backgrounds/Char_Select_bg"));
	m_startButton = Button("Start Game", sf::Vector2f(screenSize.x / 4, screenSize.y / 4), sf::Vector2f(screenSize.x / 2, screenSize.y / 2), sf::Color::Transparent, 30);
}

void CharacterSelectScreen::update(sf::Time deltaTime) {

}

void CharacterSelectScreen::handleEvents(sf::Event& ev) {
	if (ev.type == sf::Event::MouseButtonPressed && 
		ev.mouseButton.button == sf::Mouse::Button::Left) {
		auto mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);
		if (m_startButton.isClicked(mousePos)) {
			m_manager.switchScreen(std::make_unique<InGameScreen>(m_window, m_manager));
		}
	}
}

void CharacterSelectScreen::render() {

	m_backGround->draw(m_window, sf::RenderStates::Default);
	m_startButton.draw(m_window, sf::RenderStates::Default);
}