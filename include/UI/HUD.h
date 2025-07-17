#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
struct  PlayerData; // forward declaration
class Player; // forward declaration
class Ally; // forwars declaration
class PlayableObject;

class HUD {
public:
	HUD();
	void updatePlayer(const std::shared_ptr<Player>& player);
	void updateAllies(const std::vector<std::shared_ptr<Ally>>& allies);
	void draw(sf::RenderWindow& window);
private:
	sf::RectangleShape m_frame;
	class CharacterFrame {
	public:
		CharacterFrame(const std::shared_ptr<Player>& player);
		void update(const std::shared_ptr<PlayableObject>& character);
	private:
		sf::Sprite m_icon;
		sf::Text m_name;
		sf::RectangleShape m_hpBar;
		sf::RectangleShape m_potentialHpBar;
	};
};