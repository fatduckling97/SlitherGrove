#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "direction.hpp"


class Snake {
public:
										Snake();
										Snake(int tileSize, int boardWidth, int boardHeight, float moveDelay);

	void 								move();
	void 								grow();
	void 								draw(sf::RenderWindow& window);
	
	void								changeDirection(sf::Keyboard::Key key);
	void								update(sf::Time deltaTime);
	void 								reset();

	bool								checkSelfCollision() const;
	bool 								checkWallCollision() const;

	sf::Vector2i						getHeadPosition() const;
	sf::Vector2i						getTailPosition() const;
	const std::vector<sf::Vector2i>&	getSnakeBody() const;
	size_t								getLength() const;
	bool								isAlive() const;

private:
	std::vector<sf::Vector2i>			m_snakeBody;

	sf::RectangleShape					m_snakeBodyShape;

	int									m_boardWidth;	
	int									m_boardHeight;

	Direction							m_currentDirection;
	Direction							m_nextDirection;

	int									m_tileSize;
	
	float								m_moveTimer;
	float 								m_moveDelay;
	
	bool								m_alive;
	bool								m_shouldGrow;
};
