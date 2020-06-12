#ifndef Score_HEADER
#define Score_HEADER
#include "Object.h"

class Score {
public:
	int x;
	int y;
	sf::Font font;
	sf::Color color;
	sf::Text score;
	int font_size;
	Score(int x, int y, int font_size, std::string font_path, sf::Color color);
	int setFont(std::string font_path);
	sf::Text getScore();
};

sf::Text Score::getScore() {
	return score;
}

Score::Score(int x, int y, int font_size, std::string font_path, sf::Color color) {
	setFont(font_path);
	score.setFont(font);
	score.setFillColor(color);
	score.setCharacterSize(font_size);
	score.setPosition(x, y);
}

int Score::setFont(std::string font_path) {
	if (!font.loadFromFile(font_path)) {
		return 1;
	}
}

#endif