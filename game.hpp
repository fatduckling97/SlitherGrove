#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include "snake.hpp"
#include "apple.hpp"
#include "background.hpp"


class Game {
public:
								Game();
	void						run();

private:
	void						processEvents();
	void						update(sf::Time deltaTime);
	void						render();
	void						reset();

private:
	int							m_tileSize;
	int							m_boardWidth;
	int							m_boardHeight;
	float						m_moveDelay;

	sf::RenderWindow			m_window;
	sf::Clock					m_clock;

	Snake						m_snake;
	Apple						m_apple;
	Background					m_background;

	int							m_score;

	sf::Font					m_font;
	sf::Text					m_scoreText;
	sf::Text					m_gameOverText;
	sf::Text					m_restartCommandText;

	sf::SoundBuffer				m_eatBuffer;
	std::optional<sf::Sound>	m_eatSound;

	sf::SoundBuffer				m_bumpBuffer;
	std::optional<sf::Sound>	m_bumpSound;

	bool						m_gameOver;
};