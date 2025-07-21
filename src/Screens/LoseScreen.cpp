#include "Screens/LoseScreen.h"
#include "Screens/CharacterSelectScreen.h"
#include "Management/GameManager.h"
#include "Management/ResourceManager.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

LoseScreen::LoseScreen(sf::RenderWindow& window, GameManager& manager)
    : IScreen(window, manager)
{
    sf::Vector2f screenSize(static_cast<sf::Vector2f>(m_window.getSize()));

    // Load background
    m_backGround = Background(screenSize, ResourceManager::instance().getTexture("screen_backgrounds/Welcome_bg"));

    // Set up "Try Again" button
    m_startButton = Button(
        "Try Again",
        sf::Vector2f(screenSize.x / 4, screenSize.y / 4),
        sf::Vector2f(screenSize.x / 2, screenSize.y / 2),
        sf::Color::Transparent,
        30
    );
}

void LoseScreen::handleEvents(sf::Event& ev) {
    if (ev.type == sf::Event::MouseButtonPressed &&
        ev.mouseButton.button == sf::Mouse::Left) {
        auto mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);

        if (m_startButton.isClicked(mousePos)) {
            m_manager.switchScreen(std::make_unique<CharacterSelectScreen>(m_window, m_manager));
        }
    }
}

void LoseScreen::render() {
    m_backGround->draw(m_window, sf::RenderStates::Default);
    m_startButton.draw(m_window, sf::RenderStates::Default);
}
