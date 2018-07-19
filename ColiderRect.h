#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class ColiderRect : public sf::FloatRect {
	Entity* _parent;
	bool _active;
	
public:
	ColiderRect(Entity*);
	
	Entity* getParent() const { return _parent; }
	bool isActive() const { return _active; }
	
	bool colidesWith(const ColiderRect&) const;

	ColiderRect* findColision(const std::vector<ColiderRect*>) const;
};
