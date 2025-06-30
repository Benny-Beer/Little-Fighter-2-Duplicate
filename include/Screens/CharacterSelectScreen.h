#pragma once
#include "IScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"
#include <vector>

class CharacterSelectScreen : public IScreen {
public:
	CharacterSelectScreen(sf::RenderWindow& window, GameManager& manager);
	void update(sf::Time deltaTime) override;
	void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	std::optional<Background> m_backGround;
	std::vector<sf::Texture> m_characters;
	
};
