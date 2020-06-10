#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

	//start window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "GAME");
	window.setFramerateLimit(60);
	
	bool play = true;

	sf::Event event;
	//game loop
	while (play) {
		//events
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
				std::cout << "Key pressed...\n";
			}

			if (event.type == sf::Event::Closed) {
				play = false;
			}
		}

		//logic

		//rendering
		window.clear();

		window.display();
	}

	//clean up
	window.close();

	return 0;
}