#pragma once

#include "Entity.h"
#include "KeyClicks.h"

class Player : public Entity {
	const KeyClicks* _controller;
	sf::Vector2i _shakeFactor;

public:
	Player(std::vector<ColiderRect*>*, std::vector<ColiderRect*>*, const KeyClicks*);

	sf::Vector2i getShake() const { return _shakeFactor; }

	void update();
	void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
};
