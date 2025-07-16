#pragma once
#include "SFML/Graphics.hpp"
#include "Management/ResourceManager.h"
#include "Management/Animation.h"
#include "Management/AnimationManager.h"
#include "Factory/Factory.h"
#include "iostream"

class Object {
public:
	Object(const sf::Vector2f pos, const std::string& name);
	Object(std::shared_ptr<sf::Texture>textSheet);
	virtual ~Object() = default;
	virtual void handleCollision() = 0;
	virtual void update(float dt);
	
	void setAnimation(const Animation& anim);
	void setPosition(const sf::Vector2f pos);
	void setSize(float scale);
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
	const sf::Texture* getTexture();
	
	void draw(sf::RenderWindow& window) const;
	bool collide(Object& other) const;

protected:
	void setScale(int side);
	void setOrigin(float x, float y);
	sf::Vector2f getSize() const;
	sf::Sprite& getSprite();
	void updateAnimation(float dt);
	void apllySprite();
	void moveSprite(sf::Vector2f pos);
	
private:
	const sf::Texture* m_texture = nullptr;
	sf::Sprite m_sprite;
	Animation m_animation;
};
