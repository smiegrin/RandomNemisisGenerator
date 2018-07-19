#include "PlayLevel.h"
#include <iostream>

PlayLevel::PlayLevel():
	phaseCounter(0),
	animationCounter(0),
	player(&hitBoxes, &hurtBoxes)
{
	//setup healthbars

	wipeRect.setFillColor(sf::Color(0,0,0,255));
	wipeRect.setSize(sf::Vector2f(640,640));

	player.setPosition(sf::Vector2f(320,320));
	hitBoxes.push_back(player.getBodyReference());
	hurtBoxes.push_back(player.getWeaponReference());

	ColiderRect temp(nullptr);

	temp.width = 640;
	temp.height = 32;
	temp.top = 0;
	temp.left = 0;
	hitBoxes.push_back(new ColiderRect(temp));

	temp.top = 608;
	hitBoxes.push_back(new ColiderRect(temp));

	temp.width = 32;
	temp.height = 640;
	temp.top = 0;
	temp.left = 0;
	hitBoxes.push_back(new ColiderRect(temp));

	temp.left = 608;
	hitBoxes.push_back(new ColiderRect(temp));
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

		player.update(keyInfo);

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

	//draw player
	target.draw(player, states);
	//draw enemies

	sf::RectangleShape printhead;

	printhead.setFillColor(sf::Color::Green);
	for(std::vector<ColiderRect*>::const_iterator i = hitBoxes.begin();
			i != hitBoxes.end();
			i++) {
		printhead.setPosition((**i).left, (**i).top);
		printhead.setSize(sf::Vector2f((**i).width, (**i).height));
		target.draw(printhead, states);
	}

	printhead.setFillColor(sf::Color::Red);
	for (auto i : hurtBoxes) {
		printhead.setPosition(i->left, i->top);
		printhead.setSize(sf::Vector2f(i->width, i->height));
		target.draw(printhead, states);
	}

	//draw bar overlay

	target.draw(wipeRect, states);
}
