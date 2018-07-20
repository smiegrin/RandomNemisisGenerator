#pragma once

//#include "Entity.h"
#include "ColiderRect.h"
#include "KeyClicks.h"

class Player : public Entity {
	sf::Vector2i _shakeFactor;
	sf::Vector2f _groundTracker;
	ColiderRect _body;
	ColiderRect _weapon;
	ColiderRect _feet;

public:
	Player(std::vector<ColiderRect*>*, std::vector<ColiderRect*>*);

	sf::Vector2i getShake() const { return _shakeFactor; }
	ColiderRect* getBodyReference() { return &_body; }
	ColiderRect* getWeaponReference() { return &_weapon; }

	void update(const KeyClicks&);
	void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
};
