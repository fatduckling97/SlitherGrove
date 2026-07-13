#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include "direction.hpp"

struct HeadTexture {
	sf::Texture			up;
	sf::Texture			down;
	sf::Texture			left;
	sf::Texture			right;
};

struct HeadEatTexture {
	sf::Texture			up;
	sf::Texture			down;
	sf::Texture			left;
	sf::Texture			right;
};

struct BodyTexture {
	sf::Texture			up;
	sf::Texture			down;
	sf::Texture			left;
	sf::Texture			right;
};

struct BodyCornerTexture {
	sf::Texture			topLeft;
	sf::Texture			topRight;
	sf::Texture			downLeft;
	sf::Texture			downRight;
};

struct TailTexture {
	sf::Texture			up;
	sf::Texture			down;
	sf::Texture			left;
	sf::Texture			right;
};

struct SnakeTextures {
	HeadTexture			head;
	HeadEatTexture		headEat;
	
	BodyTexture			body;
	BodyCornerTexture	bodyCorner;

	TailTexture			tail;
};


class Snake {
public:
										Snake();
										Snake(int tileSize, int boardWidth, int boardHeight, float moveDelay);

	void 								move();
	void 								grow();
	void 								draw(sf::RenderWindow& window);
	void								drawHead(sf::RenderWindow& window);
	void								drawBody(sf::RenderWindow& window, size_t idx);
	void								drawTail(sf::RenderWindow& window);
	
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

	SnakeTextures						m_snakeTexture;

	std::optional<sf::Sprite>			m_snakeHeadSprite;
	std::optional<sf::Sprite>			m_snakeHeadEatSprite;
	std::optional<sf::Sprite>			m_snakeBodySprite;
	std::optional<sf::Sprite>			m_snakeBodyCornerSprite;
	std::optional<sf::Sprite>			m_snakeTailSprite;

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
