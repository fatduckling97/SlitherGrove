#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

class Background {
public:
									Background(int tileSize, int boardWidth, int boardHeight);
	void							draw(sf::RenderWindow& window);

private:
	int								m_tileSize;
	int								m_boardWidth;
	int								m_boardHeight;

	sf::Texture						m_grassTexture;
	sf::Texture						m_edgeTopTexture;
	sf::Texture						m_edgeDownTexture;
	sf::Texture						m_edgeLeftTexture;
	sf::Texture						m_edgeRightTexture;
	sf::Texture						m_edgeCornerTexture;
	
	std::optional<sf::Sprite>		m_grassSprite;
	std::optional<sf::Sprite>		m_edgeTopSprite;
	std::optional<sf::Sprite>		m_edgeDownSprite;
	std::optional<sf::Sprite>		m_edgeLeftSprite;
	std::optional<sf::Sprite>		m_edgeRightSprite;
	std::optional<sf::Sprite>		m_edgeCornerSprite;
};