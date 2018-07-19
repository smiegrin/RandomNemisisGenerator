#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class ColiderRect : sf::FloatRect {
	Entity* _parent;
	bool _active;
	
public:
	ColiderRect(Entity*);
	
	Entity* getParent() { return _parent; }
	bool isActive() { return _active; }
	
	bool colidesWith(const ColiderRect&);
};
