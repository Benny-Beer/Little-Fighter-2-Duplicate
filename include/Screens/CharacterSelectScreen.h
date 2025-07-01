#pragma once
#include "IScreen.h"
#include "UI/Background.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

class CharacterSelectScreen : public IScreen {
public:
    CharacterSelectScreen(sf::RenderWindow& window, GameManager& manager);
    void update(sf::Time deltaTime) override;
    void handleEvents(sf::Event& ev) override;
    void render() override;

private:
    std::optional<Background> m_backGround;
    sf::Font m_font;
    sf::Text m_instructionText;
    float m_opacityTime = 0.f;

    // Character frame
    sf::RectangleShape m_frame;
    sf::RectangleShape m_profilePlaceholder;
    sf::Text m_characterName;
    sf::Text m_characterDescription;
    sf::Text m_placeholderText;
};
