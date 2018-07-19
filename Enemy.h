#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy(std::vector<ColiderRect*>* hit, std::vector<ColiderRect*>* hurt) :
		Entity(hit, hurt) {}

	virtual void update() = 0;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};
