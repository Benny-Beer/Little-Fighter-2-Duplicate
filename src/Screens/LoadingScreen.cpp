#pragma once
#include "Screens/LoadingScreen.h"
#include "Screens/CharacterSelectScreen.h"
#include "Screens/IScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"
#include "Management/GameManager.h"
#include "Management/ResourceManager.h"
#include <iostream>
#include <stdexcept>

LoadingScreen::LoadingScreen(sf::RenderWindow& window, GameManager& manager) : IScreen(window, manager),
																			   m_dataLoader(DataLoader("data/data.txt"))
{
	sf::Vector2f screenSize(static_cast <sf::Vector2f> (m_window.getSize()));
	m_backGround = Background(screenSize, ResourceManager::instance().getTexture("screen_backgrounds/Loading_bg"));
	m_startButton = Button("to character select screen", sf::Vector2f(screenSize.x / 4, screenSize.y / 4), sf::Vector2f(screenSize.x / 2, screenSize.y / 2), sf::Color::Transparent, 30);
	std::cout << "LoadingState created, m_manager ptr: " << &m_manager << std::endl;
	m_dataLoader.loadCharacterDat();
}

void LoadingScreen::handleEvents(sf::Event& ev) {
	
if (ev.type == sf::Event::MouseButtonPressed && 
	ev.mouseButton.button == sf::Mouse::Button::Left) {
		auto mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);
		if (m_startButton.isClicked(mousePos)) {
			m_manager.switchScreen(std::make_unique<CharacterSelectScreen>(m_window, m_manager));
		}
	}
}

void LoadingScreen::render() {

	m_backGround->draw(m_window, sf::RenderStates::Default);
	m_startButton.draw(m_window, sf::RenderStates::Default);
}