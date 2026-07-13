#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "snake.hpp"


class Apple {
public:
									Apple();
									Apple(int tileSize, int boardWidth, int boardHeight);
	void							spawn(const std::vector<sf::Vector2i>& snakeBody);
	void							draw(sf::RenderWindow& window);
	sf::Vector2i					getApplePosition() const;

private:
	sf::Vector2i					m_applePosition;

	sf::Texture						m_appleTexture;
	std::optional<sf::Sprite>		m_appleSprite;

	int 							m_boardWidth;
	int								m_boardHeight;
	int								m_tileSize;	
};
