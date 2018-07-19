#include "ColiderRect.h"

ColiderRect::ColiderRect(Entity* parent) :
		sf::FloatRect(0,0,32.0,32.0),
		_parent(parent),
		_active(true)
{}

bool ColiderRect::colidesWith(const ColiderRect& other) const {
	return !(
		top+height < other.top ||
		top > other.top + other.height ||
		left+width < other.left ||
		left > other.left + other.width
	);
}

ColiderRect* ColiderRect::findColision(const std::vector<ColiderRect *> set) const {
	for(std::vector<ColiderRect*>::const_iterator i = set.begin(); i != set.end(); i++) {
		if((**i).getParent() == this->getParent()) continue;
		if(colidesWith(**i)) return *i;
	}
	return nullptr;
}
