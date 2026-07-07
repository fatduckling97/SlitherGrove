#pragma once

#include <SFML/Graphics.hpp>
#include "snake.hpp"
#include "apple.hpp"


class Game {
public:
						Game();
	void				run();

private:
	void				processEvents();
	void				update(sf::Time deltaTime);
	void				render();
	void				reset();

private:
	int					m_tileSize;
	int					m_boardWidth;
	int					m_boardHeight;
	float				m_moveDelay;

	sf::RenderWindow	m_window;
	sf::Clock			m_clock;

	Snake				m_snake;
	Apple				m_apple;

	int					m_score;
	bool				m_gameOver;
};