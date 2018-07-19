#include "ColiderRect.h"

ColiderRect::ColiderRect(Entity* parent) :
		sf::FloatRect(0,0,32.0,32.0),
		_parent(parent),
		_active(true)
{}

bool ColiderRect::colidesWith(const ColiderRect& other) {
	return !(
		top+height < other.top ||
		top > other.top + other.height ||
		left+width < other.left ||
		left > other.left + other.width
	);
}
