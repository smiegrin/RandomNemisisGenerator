#include "PlayLevel.h"
#include <iostream>

PlayLevel::PlayLevel():
	phaseCounter(0),
	animationCounter(0),
	player(&hitBoxes, &hurtBoxes, new KeyClicks(8))
{
	//setup healthbars

	wipeRect.setFillColor(sf::Color(0,0,0,255));
	wipeRect.setSize(sf::Vector2f(640,640));
}


void PlayLevel::initialize(const int& seed) {
	player.setHealth(1000);
}

PlayLevel::Result PlayLevel::update(KeyClicks keyInfo) {

	Result endResult = LOSE;
	if (phaseCounter == 0) {
		//start music
		wipeRect.setPosition(0, 0);
		wipeRect.setSize(sf::Vector2f(640,640));
		endResult = CONTINUING;
		phaseCounter++;
	}

	else if (phaseCounter > 0 && phaseCounter < 15) {
		wipeRect.setPosition(0, phaseCounter/15.0*640);
		endResult = CONTINUING;
		phaseCounter++;
	}

	else if (phaseCounter ==  15) { //game logic
		wipeRect.setPosition(0, -640);

		//key presses
		if (keyInfo.getDown(9)) phaseCounter++;

		if (keyInfo.getHit(0)) ;//alphaA.update(Slider::UP);
		else if (keyInfo.getHit(1)) ;//alphaA.update(Slider::RIGHT);
		else if (keyInfo.getHit(2)) ;//alphaA.update(Slider::DOWN);
		else if (keyInfo.getHit(3)) ;//alphaA.update(Slider::LEFT);
		else ;//alphaA.update(Slider::NONE);

		if (keyInfo.getHit(6)) phaseCounter = 31;
		else if (keyInfo.getHit(7)) phaseCounter++;

		//update health bars:
		//alphaHealth.setSize(sf::Vector2f(64*alphaA.getHealth(), 64));
		//betaHealth.setSize(sf::Vector2f(64*betaB.getHealth(), 64));

		//if (alphaA.getHealth() == 0 || betaB.getHealth() == 0) phaseCounter++;
		//if (alphaA.isAtGoal() && betaB.isAtGoal()) phaseCounter = 31;

		endResult = CONTINUING;
	}

	else if (phaseCounter > 15 && phaseCounter < 30) {
		wipeRect.setPosition(0, (phaseCounter - 15)/15.0*640 - 640);
		wipeRect.setFillColor(sf::Color(0,0,0,255));
		endResult = CONTINUING;
		phaseCounter++;
	}

	else if (phaseCounter == 30) {
		endResult = LOSE;
		phaseCounter = 0;
		//stop the music
	}

	else if (phaseCounter > 30 && phaseCounter < 45) {
		float percent = (phaseCounter - 30)/15.0;
		wipeRect.setPosition(320 - percent*320, 320 - percent*320);
		wipeRect.setSize(sf::Vector2f(640*percent, 640*percent));
		endResult = CONTINUING;
		phaseCounter++;
	}

	else if (phaseCounter == 45) {
		endResult = WIN;
		phaseCounter = 0;
		wipeRect.setSize(sf::Vector2f(640,640));
		wipeRect.setPosition(0,0);
		//stop the music
	}

	return endResult;
}

void PlayLevel::draw(sf::RenderTarget& target,  sf::RenderStates states = sf::RenderStates::Default) const {

	//draw enemies
	//draw player

//	target.draw(alphaHealth);
//	target.draw(betaHealth);
//	//draw bar overlay
	sf::Vector2f x = wipeRect.getPosition();
	sf::Transform y = wipeRect.getTransform();
	sf::Vector2f z = wipeRect.getSize();
	sf::RectangleShape copy(wipeRect);
//	copy.setSize(sf::Vector2f(640,640));
	sf::RectangleShape temp(sf::Vector2f(640,640));

	target.draw(copy, states);
//	target.draw(wipeRect, states);
//	target.draw(temp, states);
}
