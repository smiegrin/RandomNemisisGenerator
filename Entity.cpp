#include "Entity.h"

Entity::Entity(std::vector<ColiderRect *> * hit, std::vector<ColiderRect *> * hurt) :
		_hitWorld(hit),
		_hurtWorld(hurt)
{}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	//flag this out later:
	sf::RectangleShape printHead(_velocity);
	printHead.setPosition(_position);
	printHead.setFillColor(sf::Color(0, 0, 255, 128));
	target.draw(printHead, states);
}
