#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include "pad.h"
#include "Ball.h"
#include "Score.h"

sf::Sound configSound(std::string file_path);
int loadFromFile(sf::SoundBuffer buffer, std::string file_path);

int main() {
	
	//this is simply to supress an error caused by anne pro keyboard software
	sf::err().rdbuf(NULL);

	//start window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Julhinho's adventure");
	//general configs
	window.setFramerateLimit(60);
	
	//states for events and buttons
	bool play = true;
	bool wPressed = false;
	bool sPressed = false;
	bool upPressed = false;
	bool downPressed = false;
	
	//outside file paths
	std::string pad_texture = "data/image1.png";
	std::string ball_texture = "data/jubilu.png";
	std::string font_path = "data/arial.ttf";
	std::string back_path = "data/forest.png";
	std::string hit_path = "data/hit.wav";
	std::string theme_path = "data/theme.ogg";
	
	//objects
	Pad *pad_1 = new Pad(20, 200, pad_texture, 50, 200);
	Pad *pad_2 = new Pad(730, 200, pad_texture, 50, 200);
	Ball *ball = new Ball(300, 300, -6, -6, ball_texture, 100, 100);
	Score *score = new Score(350, 10, 30, font_path, sf::Color::Cyan);

	//background
	sf::Texture back;
	if (!back.loadFromFile(back_path)) {
		return 1;
	}
	sf::Sprite sprite;
	sf::Vector2u size = back.getSize();
	sprite.setTexture(back);

	//sounds
	sf::Sound hit_sound = configSound(hit_path);

	sf::Music back_theme;
	if (!back_theme.openFromFile(theme_path)) {
		return 1;
	}
	back_theme.setVolume(10);
	back_theme.setLoop(true);
	back_theme.play();

	//getting event
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
		ball->shape.move(ball->x_speed, ball->y_speed);
		printf("%d %d \n", ball->x_speed, ball->y_speed);

		if (ball->shape.getPosition().y < 0) {
			ball->y_speed = -ball->y_speed;
		}

		if (ball->shape.getPosition().y > 500) {
			ball->y_speed = -ball->y_speed;
		}

		if (ball->shape.getGlobalBounds().intersects(pad_1->shape.getGlobalBounds()) || ball->shape.getGlobalBounds().intersects(pad_2->shape.getGlobalBounds())) {
			ball->x_speed = -ball->x_speed;
			hit_sound.play();
		}

		if (ball->shape.getPosition().x < 0) {
			ball->shape.setPosition(300, 300);
			pad_2->points++;
		}
		if (ball->shape.getPosition().x > 800) {
			ball->shape.setPosition(300, 300);
			pad_1->points++;
		}


		//pads
		if (wPressed) {
			if (pad_1->y > 0) pad_1->y -=5;
			pad_1->shape.setPosition(pad_1->x, pad_1->y);
		}
		if (sPressed) {
			if (pad_1->y < 400) pad_1->y +=5;
			pad_1->shape.setPosition(pad_1->x, pad_1->y);
		}
		if (upPressed) {
			if (pad_2->y > 0) pad_2->y -= 5;
			pad_2->shape.setPosition(pad_2->x, pad_2->y);
		}
		if (downPressed) {
			if (pad_2->y < 400) pad_2->y += 5;
			pad_2->shape.setPosition(pad_2->x, pad_2->y);
		}

		//rendering
		window.clear();

		window.draw(sprite);
		window.draw(ball->shape);
		window.draw(pad_1->shape);
		window.draw(pad_2->shape);

		std::stringstream score_text;
		score_text << pad_1->points << " : " << pad_2->points;
		score->score.setString(score_text.str());
		window.draw(score->getScore());

		window.display();
	}

	//clean up
	window.close();

	return 0;
}

sf::Sound configSound(std::string file_path) {
	sf::SoundBuffer hit;
	loadFromFile(hit, file_path);
	sf::Sound hit_sound;
	hit_sound.setBuffer(hit);
	return hit_sound;
}

int loadFromFile(sf::SoundBuffer buffer, std::string file_path) {
	if (!buffer.loadFromFile(file_path)) {
		return 1;
	}
 }