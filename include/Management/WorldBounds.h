#include <SFML/Graphics.hpp>


class WorldBounds {
public:
    WorldBounds(const sf::FloatRect& bounds) : m_bounds(bounds) {}
    bool isInside(const sf::Vector2f& center) const; 
    sf::Vector2f clampPosition(const sf::Vector2f& pos, const sf::Vector2f& size) const;

private:
    sf::FloatRect m_bounds;
};
