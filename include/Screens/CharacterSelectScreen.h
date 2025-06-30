#pragma once
#include "IScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"

class CharacterSelectScreen : public IScreen {
public:
	CharacterSelectScreen(sf::RenderWindow& window, GameManager& manager);
	void update(sf::Time deltaTime) override;
	void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	sf::Texture m_bgTexture;
	std::optional<Background> m_backGround;
	Button m_startButton;
};
