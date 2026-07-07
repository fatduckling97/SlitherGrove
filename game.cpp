#include "game.hpp"


Game::Game()
	: m_tileSize(32)
	, m_boardWidth(25)
	, m_boardHeight(18)
	, m_moveDelay(0.15f)
	, m_window(sf::VideoMode(
		sf::Vector2u(
			static_cast<unsigned int>(m_boardWidth * m_tileSize), 
			static_cast<unsigned int>(m_boardHeight * m_tileSize)
		)
	), "Slither Grove")
	, m_snake(m_tileSize, m_boardWidth, m_boardHeight, m_moveDelay)
	, m_apple(m_tileSize, m_boardWidth, m_boardHeight)
{
	reset();
}

void Game::run()
{
	while (m_window.isOpen())
	{
		sf::Time deltaTime = m_clock.restart();

		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::processEvents()
{
	while (auto event = m_window.pollEvent()) 
	{
		if (event->is<sf::Event::Closed>())
			m_window.close();

		else if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
			m_snake.changeDirection(keyEvent->code);
	}
}

void Game::update(sf::Time deltaTime)
{
	if (m_gameOver)
	{
		return;
	}

	m_snake.update(deltaTime);

	if (!m_snake.isAlive())
	{
		m_gameOver = true;
	}

	if (m_snake.getHeadPosition() == m_apple.getApplePosition())
	{
		m_snake.grow();
		m_apple.spawn(m_snake.getSnakeBody());
		m_score++;
	}
}

void Game::render()
{
	m_window.clear();
	m_apple.draw(m_window);
	m_snake.draw(m_window);
	m_window.display();
}

void Game::reset()
{
	m_score = 0;
	m_gameOver = false;

	m_snake.reset();
	m_apple.spawn(m_snake.getSnakeBody());
}
