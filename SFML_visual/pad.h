#ifndef Pad_HEADER
#define Pad_HEADER
#include "Object.h"

class Pad:public Object {
	public:
		int points;
		Pad(int x, int y, std::string pad_texture, int x_size, int y_size);
};

Pad::Pad(int x_value, int y_value, std::string pad_texture, int x_size, int y_size) {
	x = x_value;
	y = y_value;
	points = 0;
	loadSetTexture(pad_texture);
	shape.setSize(sf::Vector2f(x_size, y_size));
	shape.setPosition(x_value, y_value);
}

#endif