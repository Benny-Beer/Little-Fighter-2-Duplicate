#include "Screens/CharacterSelectScreen.h"
#include "Screens/IScreen.h"
#include <cmath> // for std::sin

CharacterSelectScreen::CharacterSelectScreen(sf::RenderWindow& window, GameManager& manager)
    : IScreen(window,manager)
{
    // Load font
    if (!m_font.loadFromFile("assets/fonts/your_font.ttf")) {
        // handle error
    }

    // Background (optional)
    // m_backGround.emplace("assets/backgrounds/char_select_bg.png", m_window);

    // Frame box
    m_frame.setSize({ 300.f, 400.f });
    m_frame.setPosition(100.f, 100.f);
    m_frame.setFillColor(sf::Color::Transparent);
    m_frame.setOutlineColor(sf::Color::White);
    m_frame.setOutlineThickness(2.f);

    // Profile placeholder (inside frame)
    m_profilePlaceholder.setSize({ 260.f, 260.f });
    m_profilePlaceholder.setPosition(120.f, 120.f);
    m_profilePlaceholder.setFillColor(sf::Color(50, 50, 100));

    // Placeholder text
    m_placeholderText.setFont(m_font);
    m_placeholderText.setString("Press ATTACK to choose a character");
    m_placeholderText.setCharacterSize(16);
    m_placeholderText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = m_placeholderText.getLocalBounds();
    m_placeholderText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
    m_placeholderText.setPosition(
        m_profilePlaceholder.getPosition().x + m_profilePlaceholder.getSize().x / 2.f,
        m_profilePlaceholder.getPosition().y + m_profilePlaceholder.getSize().y / 2.f
    );

    // Name (empty for now)
    m_characterName.setFont(m_font);
    m_characterName.setCharacterSize(18);
    m_characterName.setFillColor(sf::Color::White);
    m_characterName.setPosition(120.f, 390.f);

    // Description (empty for now)
    m_characterDescription.setFont(m_font);
    m_characterDescription.setCharacterSize(14);
    m_characterDescription.setFillColor(sf::Color(180, 180, 180));
    m_characterDescription.setPosition(120.f, 420.f);
}

void CharacterSelectScreen::update(sf::Time deltaTime)
{
    // Animate placeholder text opacity using sine wave
    m_opacityTime += deltaTime.asSeconds();
    float alpha = 128 + 127 * std::sin(m_opacityTime * 2.f); // Pulses between 1 and 255
    sf::Color c = m_placeholderText.getFillColor();
    c.a = static_cast<sf::Uint8>(alpha);
    m_placeholderText.setFillColor(c);
}

void CharacterSelectScreen::handleEvents(sf::Event& ev)
{
    // Optional: handle input later
}

void CharacterSelectScreen::render()
{
    if (m_backGround) m_backGround->draw(m_winodw,sf::RenderStates::Default);

    m_window.draw(m_frame);
    m_window.draw(m_profilePlaceholder);
    m_window.draw(m_placeholderText);
    m_window.draw(m_characterName);
    m_window.draw(m_characterDescription);
}
