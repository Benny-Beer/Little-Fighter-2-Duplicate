#include "UI/HUD.h"
#include "Gameplay/Player.h"
#include "Gameplay/Ally.hpp"
#include "Object/PlayableObject.h"
#include <SFML/Graphics.hpp>
#include <memory>

HUD::HUD() {
    m_frame.setSize(sf::Vector2f(800, 1000));
    m_frame.setFillColor(sf::Color(0,0,102));
    m_frame.setOrigin(0.f, 0.f);
    m_frame.setPosition(0.f, 0.f);
}

void HUD::updatePlayer(const std::shared_ptr<Player>& player) {
    // The main player goes in the first frame
    // If you want to reuse an existing frame, you could store it
    CharacterFrame frame(player);
    frame.update(player);
    // You would usually store it to a vector or member here
    // For now, this is a placeholder
}

void HUD::updateAllies(const std::vector<std::shared_ptr<Ally>>& allies) {
    for (const auto& ally : allies) {
        CharacterFrame frame(nullptr);  // Player isn't needed to construct ally frame
        frame.update(ally);
        // Again, you would store the frame in a member vector to be drawn
    }
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(m_frame);

    // Here, you'd draw each stored CharacterFrame
    // For example:
    // for (auto& frame : m_characterFrames)
    //     frame.draw(window);
}

// ------------------ CharacterFrame Implementation --------------------

HUD::CharacterFrame::CharacterFrame(const std::shared_ptr<Player>& player) {
    // Dummy values for visual layout
    m_icon.setPosition(10.f, 10.f);

    m_hpBar.setSize(sf::Vector2f(100, 10));
    m_hpBar.setFillColor(sf::Color::Red);
    m_hpBar.setPosition(10.f, 50.f);

    m_potentialHpBar.setSize(sf::Vector2f(100, 10));
    m_potentialHpBar.setFillColor(sf::Color(255, 165, 0));  // Orange
    m_potentialHpBar.setPosition(10.f, 50.f);

    m_name.setCharacterSize(16);
    m_name.setFillColor(sf::Color::White);
    m_name.setPosition(10.f, 70.f);

    // If `player` isn't null, you might pull portrait/name here
    if (player) {
        if (auto texture = player->getPortrait()) {
            m_icon.setTexture(*texture);
        }
        m_name.setString(player->getName());
    }
}

void HUD::CharacterFrame::update(const std::shared_ptr<PlayableObject>& character) {
    if (!character) return;

    // Example values — replace with your actual accessors
    float hpRatio = static_cast<float>(character->getCurrentHP()) / character->getMaxHP();
    m_hpBar.setSize(sf::Vector2f(100.f * hpRatio, 10.f));

    m_name.setString(character->getName());
    if (auto texture = character->getPortrait()) {
        m_icon.setTexture(*texture);
    }
}
