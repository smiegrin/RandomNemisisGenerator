#include <iostream>
#include <SFML/Graphics.hpp>
#include "KeyClicks.h"
#include "PlayLevel.h"

class MainMenu : public sf::Drawable {
	sf::Sprite _infoOverlay,
		_characterSelector,
		_seedSelector,
		_backgroundGraphic,
		_titleGraphic,
		_alphaGraphic,
		_betaGraphic;
	sf::Texture _infoTexture,
		_characterTexture,
		_seedTexture,
		_backgroundTexture,
		_titleTexture,
		_alphaTexture,
		_betaTexture;
	TileGrid _seedDisplay;
	sf::RectangleShape _fadeRect;
	int _phaseCounter;
	int _selectorPosition;

	PlayLevel level;

public:
	enum Result {DONE, CONTINUING};
	MainMenu();
	Result update(KeyClicks);
	void draw(sf::RenderTarget&, sf::RenderStates) const;
};
