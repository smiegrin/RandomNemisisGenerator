#include "Player.h"

Player::Player(std::vector<ColiderRect *> * hit, std::vector<ColiderRect *> * hurt) :
		Entity(hit, hurt),
		_body(this),
		_weapon(this)
{
	_body.width = 16;
	_body.height = 32;
}

void Player::update(const KeyClicks& keyInfo) {
	if (keyInfo.getDown(0)) {
		if (keyInfo.getDown(1)) _velocity = sf::Vector2f(1.4, -1.4);
		else if (keyInfo.getDown(3)) _velocity = sf::Vector2f(-1.4, -1.4);
		else _velocity = sf::Vector2f(0, -2);
	}
	else if (keyInfo.getDown(2)) {
		if (keyInfo.getDown(1)) _velocity = sf::Vector2f(1.4, 1.4);
		else if (keyInfo.getDown(3)) _velocity = sf::Vector2f(-1.4, 1.4);
		else _velocity = sf::Vector2f(0, 2);
	}
	else if (keyInfo.getDown(1)) _velocity = sf::Vector2f(2, 0);
	else if (keyInfo.getDown(3)) _velocity = sf::Vector2f(-2, 0);
	else _velocity = sf::Vector2f(0,0);

	ColiderRect ghost(_body);
	ghost.left += _velocity.x;
	ghost.top += _velocity.y;
	if (ghost.findColision(*_hitWorld) != nullptr) _velocity=sf::Vector2f(0,0);

	this->displace(_velocity);

	_body.left = this->_position.x - _body.width/2;
	_body.top = this->_position.y - _body.height/2;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	Entity::draw(target, states);

	sf::RectangleShape printhead(sf::Vector2f(_body.width, _body.height));
	printhead.setPosition(_body.left, _body.top);
	printhead.setFillColor(sf::Color(0, 0, 255, 255));
	target.draw(printhead, states);

	printhead.setSize(sf::Vector2f(_weapon.width, _weapon.height));
	printhead.setPosition(_weapon.left, _weapon.top);
	printhead.setFillColor(sf::Color(255, 0, 0, 255));
	target.draw(printhead, states);
}
