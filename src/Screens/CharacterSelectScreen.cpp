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
    m_backGround = Background(screenSize, sf::Color::Black);
    
    m_frame.setSize(screenSize * 0.9f);
    m_frame.setPosition(
        (screenSize.x - m_frame.getSize().x) / 2.f,
        (screenSize.y - m_frame.getSize().y) / 2.f
    );

    m_frame.setFillColor(sf::Color(0,0,102));
    m_frame.setOutlineColor(sf::Color(102,102,225));
    m_frame.setOutlineThickness(2.f);
    
    sf::Vector2f framePos = m_frame.getPosition();
    sf::Vector2f frameSize = m_frame.getSize();
    
    m_Title.setFont(m_font);
    m_Title.setString("Character Selection");
    m_Title.setCharacterSize(38);
    m_Title.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = m_Title.getLocalBounds();
    m_Title.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    m_Title.setPosition(
        framePos.x + frameSize.x / 2.f,
        framePos.y + 30.f // adjust vertical offset from top
    );
    
    m_profilePlaceholder.setSize({ 300.f, 300.f });
    m_profilePlaceholder.setFillColor(sf::Color::Black);

    sf::Vector2f placeholderSize = m_profilePlaceholder.getSize();
    m_profilePlaceholder.setPosition(
        framePos.x + (frameSize.x - placeholderSize.x) / 2.f,
        framePos.y + (frameSize.y - placeholderSize.y) / 4.f
    );

    // Placeholder text
    m_placeholderText.setFont(m_font);
    m_placeholderText.setString("Press \nATTACK to \nchoose a character");
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

    
    sf::Texture texDavisProfile;
    sf::Texture texDavisIcon;
    sf::Texture texDavisSheet;

    texDavisSheet.loadFromFile("resources/Characters/Davis/davis_0.bmp");
    texDavisProfile.loadFromFile("resources/Characters/Davis/davis_f.bmp");
    texDavisIcon.loadFromFile("resources/Characters/Davis/davis_s.bmp");
    //initialize character vetcor. TODO : make this load dynamically from Loading screen
    m_characters.push_back({
    "Davis1",
    "Balanced fighter",
    &texDavisProfile,
    &texDavisIcon,
    &texDavisSheet
});
}

void CharacterSelectScreen::update(sf::Time deltaTime)
{
    // Animate placeholder text opacity using sine wave
    m_opacityTime += deltaTime.asSeconds();
    float alpha = 128 + 127 * std::sin(m_opacityTime * 12.f); // Pulses between 1 and 255
    sf::Color c = m_placeholderText.getFillColor();
    c.a = static_cast<sf::Uint8>(alpha);
    m_placeholderText.setFillColor(c);
}

void CharacterSelectScreen::handleEvents(sf::Event& ev)
{
    int currentIndex = 0;
    if (ev.type == sf::Event::KeyPressed) {
        if (ev.key.code == sf::Keyboard::Enter) {
            if (!m_selectionMode) {
                std::cout << "Enter pressed - character selected" << std::endl;
                m_selectionMode = true;
                m_placeholderText.setString("");

                // Show first character data
                
                m_profilePlaceholder.setTexture(m_characters[currentIndex].m_profilePic);
                m_characterName.setString(m_characters[currentIndex].m_name);
                m_characterDescription.setString(m_characters[currentIndex].m_description);
            }
        }
        else if (m_selectionMode) {
            if (ev.key.code == sf::Keyboard::Right) {
                currentIndex = (currentIndex + 1) % m_characters.size();
            }
            else if (ev.key.code == sf::Keyboard::Left) {
                currentIndex = (currentIndex + m_characters.size() - 1) % m_characters.size();
            }

            // Update content
            m_profilePlaceholder.setTexture(m_characters[currentIndex].m_profilePic);
            m_characterName.setString(m_characters[currentIndex].m_name);
            m_characterDescription.setString(m_characters[currentIndex].m_description);
        }
    }
}



void CharacterSelectScreen::render()
{
    if (m_backGround) m_backGround->draw(m_window,sf::RenderStates::Default);

    m_window.draw(m_frame);
    m_window.draw(m_Title);
    m_window.draw(m_profilePlaceholder);
    m_window.draw(m_placeholderText);
    m_window.draw(m_characterName);
    m_window.draw(m_characterDescription);
}
