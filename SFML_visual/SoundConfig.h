#ifndef Sound_HEADER
#define Sound_HEADER
#include <SFML/Audio.hpp>

	sf::Sound configSound(std::string file_path) {

		sf::SoundBuffer hit;
		loadFile(hit, file_path);
		sf::Sound hit_sound;
		hit_sound.setBuffer(hit);
		return hit_sound;
	}

	int loadFile(sf::SoundBuffer hit, std::string file_path) {
		if (!hit.loadFromFile(file_path)) {
			return 1;
		}
	}




#endif