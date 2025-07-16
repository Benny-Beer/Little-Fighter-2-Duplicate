#pragma once
#include "Management/WorldBounds.h"
#include <SFML/Graphics.hpp>
#include <iostream>

bool WorldBounds::contains(const sf::FloatRect& rect) const {
    return m_bounds.contains(rect.left, rect.top) &&
        m_bounds.contains(rect.left + rect.width, rect.top + rect.height);

}

sf::Vector2f WorldBounds::clampPosition(const sf::FloatRect& objBounds) const
{
    sf::Vector2f fixed = { objBounds.left, objBounds.top };

    if (objBounds.left < m_bounds.left) {
        std::cout << "in first if\n";
        fixed.x += m_bounds.left - objBounds.left;
    }
    if (objBounds.left + objBounds.width > m_bounds.left + m_bounds.width) {

        std::cout << "in second if, m_bounds left " << m_bounds.left + m_bounds.width << std::endl;
        std::cout << "Obj " << objBounds.left + objBounds.width << std::endl;


        fixed.x -= ((objBounds.left + objBounds.width) - (m_bounds.left + m_bounds.width));

        std::cout << "offset of 2: " << ((objBounds.left + objBounds.width) - (m_bounds.left + m_bounds.width)) << std::endl;
    }
    if (objBounds.top < m_bounds.top) {
        std::cout << "in third if\n";
        fixed.y += m_bounds.top - objBounds.top;
    }
    if (objBounds.top + objBounds.height > m_bounds.top + m_bounds.height) {
        std::cout << "in fourth if, m_bounds top " << m_bounds.top + m_bounds.height << std::endl;
        std::cout << "Obj " << objBounds.top + objBounds.height << std::endl;
        fixed.y -= ((objBounds.top + objBounds.height) - (m_bounds.top + m_bounds.height));
    }
    return fixed;
}







