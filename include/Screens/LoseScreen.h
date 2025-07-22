#pragma once
#include "IScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"

class LoseScreen : public IScreen {
public:
	LoseScreen(sf::RenderWindow& window, GameManager& manager);
	void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	std::optional<Background> m_backGround;
	Button m_startButton;
};
