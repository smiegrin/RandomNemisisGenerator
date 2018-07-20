#include "Player.h"

Player::Player(std::vector<ColiderRect *> * hit, std::vector<ColiderRect *> * hurt) :
		Entity(hit, hurt),
		_body(this),
		_weapon(this),
		_feet(this)
{
	_body.width = 48;
	_body.height = 64;
	_body.top = 320;
	_body.left = 320;
}

void Player::update(const KeyClicks& keyInfo) {
	//physics
	if (keyInfo.getDown(1) && !keyInfo.getDown(3)) {
		accelerate(sf::Vector2f(3.5f,0));
	}
	else if (keyInfo.getDown(3) && !keyInfo.getDown(1)) {
		accelerate(sf::Vector2f(-3.5f,0));
	}

	if (keyInfo.getHit(4) && _ground != nullptr) {
		accelerate(sf::Vector2f(0,-16));
	}

	ColiderRect ghost(_body);
	ghost.left += _velocity.x;
	ghost.top += _velocity.y;
	if (ghost.findColision(*_hitWorld) != nullptr) {
		while (ghost.findColision(*_hitWorld) != nullptr) {
			_velocity *= 0.9f;
			ghost = _body;
			ghost.left += _velocity.x;
			ghost.top += _velocity.y;
		}
	}

	this->displace(_velocity);
	friction(0.4f);
	if (_ground == nullptr) {
		if (keyInfo.getDown(4)) accelerate(sf::Vector2f(0,0.7f));
		else accelerate(sf::Vector2f(0,1.5f));
		if (_velocity.y > 16) _velocity.y = 16;
	}
	else if (_velocity.y > 0) _velocity.y = 0;

	//update collision boxes
	_body.left = this->_position.x - _body.width/2;
	_body.top = this->_position.y - _body.height/2;
	_feet.left = _body.left+3;
	_feet.top = _body.top + _body.height;// - 2;
	_feet.width = _body.width-6;
	_feet.height = 2;
	if (_feet.width < 1) _feet.width = 1;


	//check for grounding
	_ground = _feet.findColision(*_hitWorld);
	if (_ground != nullptr) {
		_groundTracker = sf::Vector2f(_ground->getParent()->getPosition());
	}
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {

	sf::RectangleShape printhead(sf::Vector2f(_body.width, _body.height));
	printhead.setPosition(_body.left, _body.top);
	printhead.setFillColor(sf::Color(0, 0, 0, 255));
	printhead.setOutlineColor(sf::Color::Black);
	printhead.setOutlineThickness(1);
	target.draw(printhead, states);

	printhead.setSize(sf::Vector2f(_feet.width, _feet.height));
	printhead.setPosition(_feet.left, _feet.top);
	printhead.setFillColor(sf::Color(255, 0, 0, 255));
	target.draw(printhead, states);

//	printhead.setSize(sf::Vector2f(_weapon.width, _weapon.height));
//	printhead.setPosition(_weapon.left, _weapon.top);
//	printhead.setFillColor(sf::Color(255, 0, 0, 255));
//	target.draw(printhead, states);

//	Entity::draw(target, states);
}
