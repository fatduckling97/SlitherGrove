#include <iostream>
#include <cstdlib>
#include "loaders.hpp"


void loadTexture(sf::Texture& texture, const std::string& filename)
{
	if (!texture.loadFromFile(filename))
	{
		std::cerr << "Error loading " << filename << "\n" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void loadSoundBuffer(sf::SoundBuffer& buffer, const std::string& filename)
{
    if (!buffer.loadFromFile(filename))
    {
		std::cerr << "Error loading " << filename << "\n" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void loadFont(sf::Font& font, const std::string& filename)
{
	if (!font.openFromFile(filename))
	{
		std::cerr << "Error loading " << filename << "\n" << std::endl;
		exit(EXIT_FAILURE);
	}
}