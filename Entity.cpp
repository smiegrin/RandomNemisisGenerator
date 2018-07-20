#include "Entity.h"

Entity::Entity(std::vector<ColiderRect *> * hit, std::vector<ColiderRect *> * hurt) :
		_position(320,320),
		_velocity(0,0),
		_ground(nullptr),
		_hitWorld(hit),
		_hurtWorld(hurt)
{}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	//flag this out later:
	sf::RectangleShape printHead(_velocity);
	printHead.setPosition(_position);
	printHead.setFillColor(sf::Color(0, 0, 255, 128));
	target.draw(printHead, states);

	printHead.setPosition(_sprite.getPosition() - sf::Vector2f(-5,-5));
	printHead.setSize(sf::Vector2f(10,10));
	printHead.setFillColor(sf::Color(255, 255, 0, 128));
	target.draw(printHead, states);
}
