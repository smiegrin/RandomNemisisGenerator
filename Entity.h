#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
//#include "ColiderRect.h"
class ColiderRect;

class Entity : public sf::Drawable {
protected:
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	ColiderRect* _ground;
	sf::Sprite _sprite;
	int _facing;
	int _animationCounter;
	int _health;
	std::vector<ColiderRect*>* _hitWorld;
	std::vector<ColiderRect*>* _hurtWorld;

public:
	Entity(std::vector<ColiderRect*>*, std::vector<ColiderRect*>*);

	sf::Vector2f getPosition() const { return _position; }
	sf::Vector2f getVelocity() const { return _velocity; }
	ColiderRect* getGroudnd() const { return _ground; }
	sf::Sprite getSprite() const { return _sprite; }
	int getFacing() const { return _facing; }
	//animation counter?
	int getHealth() const { return _health; }

	void setPosition(const sf::Vector2f& position) { _position = position; }
	void setVelocity(const sf::Vector2f& velocity) { _velocity = velocity; }
	void setSprite(const sf::Sprite& sprite) { _sprite = sprite; }
	void setFacing(const int& direction) { _facing = (direction > 0) ? 1 : -1; }
	void setHealth(const int& health) { _health = health; }

	void displace(const sf::Vector2f& displacement) { _position += displacement; }
	void accelerate(const sf::Vector2f& acceleration) { _velocity += acceleration; }
	void friction(const float& factor) { _velocity = sf::Vector2f(_velocity.x*factor, _velocity.y); }
	void flip() { _facing *= -1; }
	void hurt(const int& damage) { _health -= damage; }

	void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
};
