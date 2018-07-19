#include "Player.h"

Player::Player(std::vector<ColiderRect *> * hit, std::vector<ColiderRect *> * hurt, const KeyClicks * controller) :
		Entity(hit, hurt),
		_controller(controller)
{}

void Player::update() {}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	Entity::draw(target, states);
}
