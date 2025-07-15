#pragma once
#include "Management/WorldBounds.h"
#include <SFML/Graphics.hpp>

bool WorldBounds::isInside(const sf::Vector2f& center) const {
    return m_bounds.contains(center);
}


sf::Vector2f WorldBounds::clampPosition(const sf::Vector2f& pos, const sf::Vector2f& size) const
{
    // ממיר מיקום (שהוא תחתית) למרכז
    sf::Vector2f center = { pos.x, pos.y - size.y / 2.f };

    // מחשב גבולות בטוחים עבור center לפי size
    float minX = m_bounds.left;
    float maxX = m_bounds.left + m_bounds.width;
    float minY = m_bounds.top + size.y / 2.f;
    float maxY = m_bounds.top + m_bounds.height - size.y / 2.f;

    float clampedX = std::max(minX, std::min(center.x, maxX));
    float clampedY = std::max(minY, std::min(center.y, maxY));

    // ממיר חזרה למיקום (שהוא תחתית)
    return { clampedX, clampedY + size.y / 2.f };
}
