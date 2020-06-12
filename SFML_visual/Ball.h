#ifndef Ball_HEADER
#define Ball_HEADER
#include "Object.h"

class Ball:public Object {
public:
	float x_speed;
	float y_speed;
	Ball(int x, int y, float x_speed, float y_speed, std::string texture_path, int xsize, int ysize);
};

Ball::Ball(int x, int y, float x_sp, float y_sp, std::string texture_path, int xsize, int ysize) {
	x_speed = x_sp;
	y_speed = y_sp;
	loadSetTexture(texture_path);
	shape.setSize(sf::Vector2f(xsize, ysize));
	shape.setPosition(x, y);
}

#endif