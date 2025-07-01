#include "Screens/CharacterSelectScreen.h"
#include "Screens/IScreen.h"
#include "Management/ResourceManager.h"
#include <cmath> // for std::sin

CharacterSelectScreen::CharacterSelectScreen(sf::RenderWindow& window, GameManager& manager)
    : IScreen(window,manager)
{
    // Load font
    if (m_font.getInfo().family.empty()) {
        if (!m_font.loadFromFile("C:/Windows/Fonts/arialbd.ttf")) {
            throw std::runtime_error("Font failed to load!");
        }
    }
    sf::Vector2f screenSize = static_cast<sf::Vector2f>(m_window.getSize());
    // Background (optional)
    m_backGround = Background(screenSize, ResourceManager::instance().getTexture("screen_backgrounds/Char_Select_bg"));
    
    m_frame.setSize(screenSize * 0.9f);
    m_frame.setPosition(
        (screenSize.x - m_frame.getSize().x) / 2.f,
        (screenSize.y - m_frame.getSize().y) / 2.f
    );

    m_frame.setFillColor(sf::Color(0,0,51));
    m_frame.setOutlineColor(sf::Color::White);
    m_frame.setOutlineThickness(2.f);

    
    m_profilePlaceholder.setSize({ 350.f, 350.f });
    m_profilePlaceholder.setFillColor(sf::Color::Black);

    sf::Vector2f framePos = m_frame.getPosition();
    sf::Vector2f frameSize = m_frame.getSize();
    sf::Vector2f placeholderSize = m_profilePlaceholder.getSize();
    m_profilePlaceholder.setPosition(
        framePos.x + (frameSize.x - placeholderSize.x) / 2.f,
        framePos.y + (frameSize.y - placeholderSize.y) / 15.f
    );

    // Placeholder text
    m_placeholderText.setFont(m_font);
    m_placeholderText.setString("Press\n ATTACK to \nchoose a character");
    m_placeholderText.setCharacterSize(20);
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
    float alpha = 128 + 127 * std::sin(m_opacityTime * 4.f); // Pulses between 1 and 255
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
    if (m_backGround) m_backGround->draw(m_window,sf::RenderStates::Default);

    m_window.draw(m_frame);
    m_window.draw(m_profilePlaceholder);
    m_window.draw(m_placeholderText);
    m_window.draw(m_characterName);
    m_window.draw(m_characterDescription);
}
