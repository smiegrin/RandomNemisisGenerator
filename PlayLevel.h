#pragma once

#include "KeyClicks.h"
#include "TileGrid.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>

class PlayLevel : public sf::Drawable {

	int seed;
	int score;
	int ticks;

	int frameCount;
  int phaseCounter;
  int animationCounter;
	sf::RectangleShape wipeRect;

	std::vector<ColiderRect*> hitBoxes;
	std::vector<ColiderRect*> hurtBoxes;
	std::vector<Enemy> enemies;
	Entity _roomBody;
	Player player;

	// Timer Display
	sf::RectangleShape health;


  //sf::Sprite healthOverlay
	//sf::Sprite foreground
	//sf::Sprite background

public:
  enum Result {WIN, LOSE, CONTINUING};

  PlayLevel();

	void initialize(const int&);

  Result update(KeyClicks);

  void draw(sf::RenderTarget&,  sf::RenderStates) const;
};
