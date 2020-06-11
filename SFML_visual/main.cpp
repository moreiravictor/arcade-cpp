#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>

int main() {
	
	//this is simply to supress an error caused by anne pro keyboard software
	sf::err().rdbuf(NULL);

	//start window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Julhinho's adventure");
	//general configs
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(true);
	
	//states for events and buttons
	bool play = true;
	bool wPressed = false;
	bool sPressed = false;
	bool upPressed = false;
	bool downPressed = false;

	//vars
	float rect_1X = 20, rect_1Y = 200, rect_1points = 0;
	float rect_2X = 730, rect_2Y = 200, rect_2points = 0;
	float ballSpeedX = -6, ballSpeedY = -6;

	//font
	sf::Font arial;
	if (!arial.loadFromFile("data/arial.ttf")) {
		return 1;
	}

	//score
	sf::Text score;
	score.setFont(arial);
	score.setFillColor(sf::Color::Cyan);
	score.setCharacterSize(30);
	score.setPosition(350, 10);

	//images
	sf::Texture wood;
	if (!wood.loadFromFile("data/image1.png")) {
		return 1;
	}

	sf::Texture back;
	if (!back.loadFromFile("data/forest.png")) {
		return 1;
	}
	sf::Sprite sprite;
	sf::Vector2u size = back.getSize();
	sprite.setTexture(back);

	sf::Texture jubilu;
	if (!jubilu.loadFromFile("data/jubilu.png")) {
		return 1;
	}


	//render shapes
	sf::RectangleShape rect_1;
	rect_1.setTexture(&wood);
	rect_1.setSize(sf::Vector2f(50, 200));
	rect_1.setPosition(rect_1X, rect_1Y);

	sf::RectangleShape rect_2;
	rect_2.setTexture(&wood);
	rect_2.setSize(sf::Vector2f(50, 200));
	rect_2.setPosition(rect_2X, rect_2Y);

	sf::RectangleShape ball;
	ball.setTexture(&jubilu);
	ball.setSize(sf::Vector2f(100, 100));
	ball.setPosition(300, 300);



	//sounds
	sf::SoundBuffer hit;
	if (!hit.loadFromFile("data/hit.wav")) {
		return 1;
	}
	sf::Sound hit_sound;
	hit_sound.setBuffer(hit);

	sf::Music back_theme;
	if (!back_theme.openFromFile("data/theme.ogg")) {
		return 1;
	}
	back_theme.setVolume(10);
	back_theme.setLoop(true);
	back_theme.play();

	sf::Event event;
	//game loop
	while (play) {
		//events
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				play = false;
			}

			//movement events
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					wPressed = true;
				}
				if (event.key.code == sf::Keyboard::S) {
				sPressed = true;
				}
				if (event.key.code == sf::Keyboard::Up) {
					upPressed = true;
				}
				if (event.key.code == sf::Keyboard::Down) {
					downPressed = true;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					wPressed = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					sPressed = false;
				}
				if (event.key.code == sf::Keyboard::Up) {
					upPressed = false;
				}
				if (event.key.code == sf::Keyboard::Down) {
					downPressed = false;
				}
			}
		}

		//logic

		//ball
		ball.move(ballSpeedX, ballSpeedY);

		if (ball.getPosition().y < 0) {
			ballSpeedY = -ballSpeedY;
		}

		if (ball.getPosition().y > 400) {
			ballSpeedY = -ballSpeedY;
		}

		if (ball.getGlobalBounds().intersects(rect_1.getGlobalBounds()) || ball.getGlobalBounds().intersects(rect_2.getGlobalBounds())) {
			ballSpeedX = -ballSpeedX;
			hit_sound.play();
		}

		if (ball.getPosition().x < 0) {
			ball.setPosition(300, 300);
			rect_2points++;
		}
		if (ball.getPosition().x > 800) {
			ball.setPosition(300, 300);
			rect_1points++;
		}


		//pads
		if (wPressed) {
			if (rect_1Y > 0) rect_1Y-=5;
			rect_1.setPosition(rect_1X, rect_1Y);
		}
		if (sPressed) {
			if (rect_1Y < 400) rect_1Y+=5;
			rect_1.setPosition(rect_1X, rect_1Y);
		}
		if (upPressed) {
			if (rect_2Y > 0) rect_2Y -= 5;
			rect_2.setPosition(rect_2X, rect_2Y);
		}
		if (downPressed) {
			if (rect_2Y < 400) rect_2Y += 5;
			rect_2.setPosition(rect_2X, rect_2Y);
		}

		//rendering
		window.clear();

		window.draw(sprite);
		window.draw(ball);
		window.draw(rect_1);
		window.draw(rect_2);

		std::stringstream score_text;
		score_text << rect_1points << " : " << rect_2points;
		score.setString(score_text.str());
		window.draw(score);

		window.display();
	}

	//clean up
	window.close();

	return 0;
}