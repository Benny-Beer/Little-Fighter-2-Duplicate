#pragma once
#include "SFML/Graphics.hpp"
#include "Management/ResourceManager.h"
#include "Management/Animation.h"
#include "Management/AnimationManager.h"
#include "Factory/Factory.h"
#include "Management/WorldBounds.h"
#include "iostream"

class Object {
public:
	Object(const sf::Vector2f pos, const std::string& name);
	virtual ~Object() = default;
	virtual void handleCollision() = 0;
	void draw(sf::RenderWindow& window) const;
	const sf::Texture* getTexture();
	void setAnimation(const Animation& anim);
	void setPosition(const sf::Vector2f pos);
	
	virtual void update(float dt);
	bool collide(Object& other)const;
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition() const;
	void setSize(float scale);
	sf::Vector2f getGeometricCenter() const;
protected:
	void updateAnimation(float dt);
	void apllySprite();
	void moveSprite(sf::Vector2f pos);
	void setScale(int side);
	void setOrigin(float x, float y);
	sf::Vector2f getSize() const;
	sf::Sprite& getSprite();
	
private:
	sf::Sprite m_sprite;
	const sf::Texture* m_texture = nullptr;
	WorldBounds m_bounds = sf::FloatRect(-25, 380, 1050, 420); // x of leftUpCorner, y of leftUpCorner, width, height  

	Animation m_animation;
	
};
