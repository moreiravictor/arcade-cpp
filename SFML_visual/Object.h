#ifndef Object_HEADER
#define Object_HEADER
#include <SFML/Graphics.hpp>

class Object {
public:
	int x;
	int y;
	sf::RectangleShape shape;
	sf::Texture texture;
	int loadSetTexture(std::string image_path);
};

int Object::loadSetTexture(std::string image_path) {
	if (!texture.loadFromFile(image_path)) {
		return 1;
	}
	shape.setTexture(&texture);
}

#endif