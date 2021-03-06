#include "MainMenu.h"

MainMenu::MainMenu() :
	_seedDisplay(
		"Graphics/hexfont.png",
		sf::Vector2i(16,16),
		sf::RectangleShape(sf::Vector2f(64,16)),
		sf::Color::Transparent
	),
	_highscoreDisplay(
		"Graphics/hexfont.png",
		sf::Vector2i(16,16),
		sf::RectangleShape(sf::Vector2f(160,16)),
		sf::Color::Transparent
	),
	_phaseCounter(0),
	_selectorPosition(0)
{
	// info overlay
	_infoTexture.loadFromFile("Graphics/Title_Infoframe.png");
	_infoOverlay.setTexture(_infoTexture);
	_infoOverlay.setPosition(208, 408);

	// Selector arrows
	_arrowTexture.loadFromFile("Graphics/arrow.png");
	_upArrow.setTexture(_arrowTexture);
	_upArrow.setPosition(-500, -500);
	_upArrow.setScale(1,-1);
	_downArrow.setTexture(_arrowTexture);
	_downArrow.setPosition(-500, -500);

	// seed selector
	_selectedSeed[0] = 15;
	_selectedSeed[1] = 14;
	_selectedSeed[2] = 2;
	_selectedSeed[3] = 1;
	for (int i = 0; i < 4; i++)
		_seedDisplay.setTile(i,0, _selectedSeed[i]);
	_seedDisplay.refreshAll();

	for (int i = 0; i < 10; i++)
		_highscoreDisplay.setTile(i,0, 0);
	_highscoreDisplay.refreshAll();

	// background
	_backgroundTexture.loadFromFile("Graphics/Title_Background.png");
	_backgroundGraphic.setTexture(_backgroundTexture);
	_backgroundGraphic.setPosition(sf::Vector2f(0,0));

	// title
	_titleTexture.loadFromFile("Graphics/Title_Lettering.png");
	_titleGraphic.setTexture(_titleTexture);
	_titleGraphic.setPosition(0, -250);

	// alpha
	_alphaTexture.loadFromFile("Graphics/Title_Alpha.png");
	_alphaGraphic.setTexture(_alphaTexture);
	_backgroundGraphic.setPosition(sf::Vector2f(-500,-500));

	// beta
	_betaTexture.loadFromFile("Graphics/Title_Beta.png");
	_betaGraphic.setTexture(_betaTexture);
	_betaGraphic.setPosition(sf::Vector2f(-500,-500));

	//Fade Rectangle
	_fadeRect.setFillColor(sf::Color(0,0,0,255));
	_fadeRect.setSize(sf::Vector2f(640, 640));
	_fadeRect.setPosition(0,0);

	//Seed Display
	_seedDisplay.setPosition(sf::Vector2f(408,228));
	_seedDisplay.setBackgroundColor(sf::Color::Transparent);
//	_seedDisplay.setTileSize(sf::Vector2i(16,16));

	//Score Display
	_highscoreDisplay.setPosition(sf::Vector2f(408, 350));
	_seedDisplay.setBackgroundColor(sf::Color::Transparent);
}

MainMenu::Result MainMenu::update(KeyClicks keyInfo)
{
	/* phase table
		0   -   11    Fade in Background
		12  -   23		Roll in Alpha
		24	-		35		Roll in Beta
		36	-		47		Roll in title
		48	-		59		Awesome flash
		60            wait for input
									BACK -> exit
									SELECT -> 61
		61  -   120   fade out
		120           delegate to game
	*/

	if (_phaseCounter == 0) { // Initialize
		//colors
		_infoOverlay.setColor(sf::Color::Transparent);
		_characterSelector.setColor(sf::Color::Transparent);
		_seedSelector.setColor(sf::Color::Transparent);

		//positions
		_backgroundGraphic.setPosition(0,0);
		_alphaGraphic.setPosition(-200, 340);
		_betaGraphic.setPosition(-250, 340);
		_titleGraphic.setPosition(70, -250);
		_infoOverlay.setPosition(400, 220);
		_seedDisplay.setPosition(-500, -500);
		_upArrow.setPosition(-500,-500);
		_downArrow.setPosition(-500,-500);
		_highscoreDisplay.setPosition(-500, -500);

		//start the music

		_phaseCounter++;
		return CONTINUING;
	}

	else if (_phaseCounter > 0 && _phaseCounter <= 11) { // Background
		float percent = _phaseCounter / 11.0f;

		_fadeRect.setFillColor(sf::Color(0,0,0,255-(255*percent)));

		_phaseCounter++;
		return CONTINUING;
	}

	else if (_phaseCounter >= 12 && _phaseCounter <= 23) { // Alpha
		float percent = (_phaseCounter - 12) / 11.0f;

		_alphaGraphic.setPosition(-300*(percent-1)*(percent-1) + 50, 320);

		_phaseCounter++;
		return CONTINUING;
	}

	else if (_phaseCounter >= 24 && _phaseCounter <= 35) { // Beta
		float percent = (_phaseCounter - 24) / 11.0f;

		_betaGraphic.setPosition(-740*(percent-1)*(percent-1) + 240, 320);

		_phaseCounter++;
		return CONTINUING;
	}

	else if (_phaseCounter >= 36 && _phaseCounter <= 47) { // Title
		float percent = (_phaseCounter - 36) / 11.0f;

		_titleGraphic.setPosition(70, -570*(percent-1)*(percent-1) + 30);

		_phaseCounter++;
		return CONTINUING;
	}

	else if (_phaseCounter >= 48 && _phaseCounter <= 59) { // Flash
		if (_phaseCounter == 48) { //pull out the interface
			_infoOverlay.setColor(sf::Color::White);
			_seedDisplay.setPosition(408,228);
			_highscoreDisplay.setPosition(425, 325);
			_downArrow.setPosition(150, 300);
		}
		float percent = (_phaseCounter - 48) / 11.0f;

		_fadeRect.setFillColor(sf::Color(255, 255, 255, 255 - percent*255));

		_phaseCounter++;
		return CONTINUING;
	}

	else if (_phaseCounter == 60) {// Menu phase
		if (keyInfo.getHit(7)) { //exit
			return DONE;
		}

		//directional logic
		if (keyInfo.getHit(0) && !(_selectorPosition == 0 || _selectorPosition == 1)) { //up
			int seedIndex = _selectorPosition - 2;
			if (_selectedSeed[seedIndex] == 15) _selectedSeed[seedIndex] = 0;
			else _selectedSeed[seedIndex]++;

			_seedDisplay.setTile(seedIndex, 0, _selectedSeed[seedIndex]);
			_seedDisplay.refresh(seedIndex, 0);
		}
		if (keyInfo.getHit(2) && !(_selectorPosition == 0 || _selectorPosition == 1)) { //down
			int seedIndex = _selectorPosition - 2;
			if (_selectedSeed[seedIndex] == 0) _selectedSeed[seedIndex] = 15;
			else _selectedSeed[seedIndex]--;

			_seedDisplay.setTile(seedIndex, 0, _selectedSeed[seedIndex]);
			_seedDisplay.refresh(seedIndex, 0);
		}
		if (keyInfo.getHit(3)) { //left
			if (_selectorPosition == 0) _selectorPosition = 5;
			else _selectorPosition--;
		}
		if (keyInfo.getHit(1)) { //right
			if (_selectorPosition == 5) _selectorPosition = 0;
			else _selectorPosition++;
		}

		//selector logic
		if (keyInfo.getHit(4)) { //z
			if (_selectorPosition < 2) { // character selected
				//stop the music
				//play start sound
				_phaseCounter++; //start game
			}
			else {
				_selectorPosition = 0;
			}
		}
		if (keyInfo.getHit(5)) { //x
			if (_selectorPosition < 2) { // character selected
				_selectorPosition = 2; // jump to seed selector
			}
		}
		if (keyInfo.getHit(6)) { //enter
			//stop the music
			//play start sound
			_phaseCounter++;
		}

		// position arrows based on selector position
		switch (_selectorPosition) {
			case 0:
				_upArrow.setPosition(-500,-500);
				_downArrow.setPosition(150,300);
				break;
			case 1:
				_upArrow.setPosition(-500,-500);
				_downArrow.setPosition(300,300);
				break;
			case 2:
				_upArrow.setPosition(406,216);
				_downArrow.setPosition(406,256);
				break;
			case 3:
				_upArrow.setPosition(422,216);
				_downArrow.setPosition(422,256);
				break;
			case 4:
				_upArrow.setPosition(438,216);
				_downArrow.setPosition(438,256);
				break;
			case 5:
				_upArrow.setPosition(454,216);
				_downArrow.setPosition(454,256);
				break;
		}

		return CONTINUING;
	}

	else if (_phaseCounter > 60 && _phaseCounter < 120) {//fade out phase
		_fadeRect.setFillColor(sf::Color(0,0,0,(int) (_phaseCounter*255.0/60.0)));
		_phaseCounter++;
		return CONTINUING;
	}

	else if (_phaseCounter == 120) {//go to level select
		//delegate to level select
		PlayLevel::Result result = level.update(keyInfo);
		if (result != PlayLevel::CONTINUING) _phaseCounter = 0;
		return CONTINUING;
	}

	return DONE;
}


void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
	if (_phaseCounter == 120) {
		target.draw(level);
	}
	else {
		target.draw(_backgroundGraphic, states);
		target.draw(_betaGraphic, states);
		target.draw(_alphaGraphic, states);
		target.draw(_titleGraphic, states);
		target.draw(_seedDisplay, states);
		target.draw(_infoOverlay, states);
		target.draw(_highscoreDisplay, states);
		target.draw(_upArrow, states);
		target.draw(_downArrow, states);
		target.draw(_fadeRect, states);
	}
}
