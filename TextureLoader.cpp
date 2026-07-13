#include <iostream>
#include <cstdlib>
#include "TextureLoader.hpp"


void loadTexture(sf::Texture& texture, const std::string& filename)
{
	if (!texture.loadFromFile(filename))
	{
		std::cerr << "Error loading from " << filename << "!\n" << std::endl;
		exit(EXIT_FAILURE);
	}
}