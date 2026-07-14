#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

void loadTexture(sf::Texture& texture, const std::string& filename);
void loadSoundBuffer(sf::SoundBuffer& buffer, const std::string& filename);
void loadFont(sf::Font& font, const std::string& filename);