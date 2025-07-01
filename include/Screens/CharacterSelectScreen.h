#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "IScreen.h"
#include "UI/Background.h"
#include "Gameplay/Player.h"

class CharacterSelectScreen : public IScreen {
public:
    CharacterSelectScreen(sf::RenderWindow& window, GameManager& manager);
    void update(sf::Time deltaTime) override;
    void handleEvents(sf::Event& ev) override;
    void render() override;

private:
    std::vector<PlayerData> m_characters;
    bool m_selectionMode = false;
    bool m_selected = false;
    // General UI
    sf::RectangleShape m_frame;
    sf::Text m_instructionText;
    sf::Text m_Title;
    std::optional<Background> m_backGround;
    sf::Font m_font;
    float m_opacityTime = 0.f;

    // Character frame
    sf::RectangleShape m_profilePlaceholder;
    sf::Text m_characterName;
    sf::Text m_characterDescription;
    sf::Text m_placeholderText;
};
