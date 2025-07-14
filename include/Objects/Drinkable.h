#pragma once
#include "Objects/PickableObject.h"

class Drinkable : public PickableObject {
public:
	Drinkable(const sf::Vector2f pos, const std::string& name);
private:
};