#include "Objects/Object.h"

Object::Object(const sf::Vector2f pos, const std::string& name)
{
	m_texture = &ResourceManager::instance().getTexture(name);
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(40.f, 80.f); // 80 / 2
	m_sprite.setPosition(pos);
	
}

void Object::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

const sf::Texture* Object::getTexture()
{
	return m_texture;
}

void Object::setAnimation(const Animation& anim)
{
	m_animation = anim;
	m_sprite.setOrigin(m_animation.getCurrentSize().x / 2.f, m_animation.getCurrentSize().y);
	m_animation.reset();
}

void Object::setPosition(const sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void Object::update(float dt)
{	
	m_animation.applyToSprite(m_sprite);

}

bool Object::collide(Object& other) const
{
	sf::FloatRect thisBounds = m_sprite.getGlobalBounds();
	sf::FloatRect otherBounds = other.getGlobalBounds();

	// הקטנה או הגדלה של גבולות – לפי הצורך שלך
	const float buffer = -20.f; // <0: הקטנה של הקופסה (מדויקת יותר), >0: הגדלה (רכה יותר)

	thisBounds.left -= buffer;
	thisBounds.top -= buffer;
	thisBounds.width += 2 * buffer;
	thisBounds.height += 2 * buffer;

	return thisBounds.intersects(otherBounds);
}

sf::FloatRect Object::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Object::getPosition() const
{

	return m_sprite.getPosition();

}

void Object::setSize(float scale)
{
	m_sprite.setScale(scale, scale);
}



void Object::updateAnimation(float dt)
{
	m_animation.update(dt);
}

void Object::apllySprite()
{
	m_animation.applyToSprite(m_sprite);
}

void Object::moveSprite(sf::Vector2f pos)
{
	m_sprite.move(pos);
}

void Object::setScale(int side)
{
	auto scale = m_sprite.getScale();
    float absX = std::abs(scale.x);
    m_sprite.setScale(side * absX, scale.y);
}

void Object::setOrigin(float x, float y)
{
	m_sprite.setOrigin(x, y);

}

sf::Vector2f Object::getSize() const
{
	return m_animation.getCurrentSize();
}

sf::Sprite& Object::getSprite() {
	return m_sprite;
}

//const sf::Sprite& Object::getSprite() const {
//	return m_sprite;
//}
