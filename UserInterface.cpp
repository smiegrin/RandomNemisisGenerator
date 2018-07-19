#include "MainMenu.h"
#include "KeyClicks.h"
#include <SFML/Graphics.hpp>

int main() {
	KeyClicks keyInfo(8); //10 stands for ten possible keys to map
	MainMenu mainMenu;
	sf::RenderWindow window(sf::VideoMode(640,640), "Alpha Beta", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		//event polling
		sf::Event event;
		keyInfo.timeStep();
		MainMenu::Result menuResult = MainMenu::CONTINUING;
		while (window.pollEvent(event)) {
			//window
			if (event.type == sf::Event::Closed) window.close();

			//keyboard
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) keyInfo.hitKey(0); //up
				if (event.key.code == sf::Keyboard::Right) keyInfo.hitKey(1); //right
				if (event.key.code == sf::Keyboard::Down) keyInfo.hitKey(2); //down
				if (event.key.code == sf::Keyboard::Left) keyInfo.hitKey(3); //left
				if (event.key.code == sf::Keyboard::Z) keyInfo.hitKey(4); //z
				if (event.key.code == sf::Keyboard::X) keyInfo.hitKey(5); //x
				if (event.key.code == sf::Keyboard::Return) keyInfo.hitKey(6); //enter
				if (event.key.code == sf::Keyboard::Escape) keyInfo.hitKey(7); //escape
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Up) keyInfo.upKey(0); //up
				if (event.key.code == sf::Keyboard::Right) keyInfo.upKey(1); //right
				if (event.key.code == sf::Keyboard::Down) keyInfo.upKey(2); //down
				if (event.key.code == sf::Keyboard::Left) keyInfo.upKey(3); //left
				if (event.key.code == sf::Keyboard::Z) keyInfo.upKey(4); //z
				if (event.key.code == sf::Keyboard::X) keyInfo.upKey(5); //x
				if (event.key.code == sf::Keyboard::Return) keyInfo.upKey(6); //Return
				if (event.key.code == sf::Keyboard::Escape) keyInfo.upKey(7); //Escape
			}
		}
		//MainMenu::Result menuResult = MainMenu::CONTINUING;
		menuResult = mainMenu.update(keyInfo); //delegate update logic
		if (menuResult == MainMenu::DONE) window.close();

		//draw steps
		window.clear(sf::Color(64,64,64,255));
		window.draw(mainMenu);
		window.display();
	}
	return 1;
}
