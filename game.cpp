#include "game.hpp"


Game::Game()
	: m_tileSize(32)
	, m_boardWidth(50)
	, m_boardHeight(30)
	, m_moveDelay(0.15f)
	, m_window(sf::VideoMode(
		sf::Vector2u(
			static_cast<unsigned int>(m_boardWidth * m_tileSize), 
			static_cast<unsigned int>(m_boardHeight * m_tileSize)
		)
	), "Slither Grove")
	, m_snake(m_tileSize, m_boardWidth, m_boardHeight, m_moveDelay)
	, m_apple(m_tileSize, m_boardWidth, m_boardHeight)
	, m_scoreText(m_font)
	, m_gameOverText(m_font)
	, m_restartCommandText(m_font)
{
	if (!m_font.openFromFile("C:\\Users\\fcel2\\source\\repos\\SlitherGrove\\nintendo.ttf"))
	{
		std::cerr << "Error load nintendo.ttf file!" << std::endl;
		exit(-1);
	}

	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(24);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_scoreText.setPosition({10.f, 10.f});

	m_gameOverText.setFont(m_font);
	m_gameOverText.setCharacterSize(36);
	m_gameOverText.setFillColor(sf::Color::White);
	m_gameOverText.setString("GAME OVER");
	sf::Rect<float> gameOverTextSize = m_gameOverText.getLocalBounds();
	m_gameOverText.setPosition(
		sf::Vector2f(
			static_cast<float>((m_window.getSize().x - gameOverTextSize.size.x) / 2.f),
			static_cast<float>((m_window.getSize().y - gameOverTextSize.size.y) / 2.f)
		)
	);

	m_restartCommandText.setFont(m_font);
	m_restartCommandText.setCharacterSize(20);
	m_restartCommandText.setFillColor(sf::Color::White);
	m_restartCommandText.setString("Press R to restart!");
	sf::Rect<float> restartTextSize = m_restartCommandText.getLocalBounds();
	m_restartCommandText.setPosition(
		sf::Vector2f(
			static_cast<float>((m_window.getSize().x - restartTextSize.size.x) / 2.f), 
			static_cast<float>((m_window.getSize().y / 2.f) + gameOverTextSize.size.y)
		)
	);
	
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
		{
			if (m_gameOver)
			{
				if (keyEvent->code == sf::Keyboard::Key::R)
				{
					reset();
				}
			}
			else
			{
				m_snake.changeDirection(keyEvent->code);
			}
		}
			
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
		m_scoreText.setString("Score: " + std::to_string(m_score));
	}
}

void Game::render()
{
	m_window.clear();
	m_apple.draw(m_window);
	m_snake.draw(m_window);
	m_window.draw(m_scoreText);
	
	if (m_gameOver)
	{
		m_window.draw(m_gameOverText);
		m_window.draw(m_restartCommandText);
	}
	
	m_window.display();
}

void Game::reset()
{
	m_score = 0;
	m_scoreText.setString("Score: " + std::to_string(m_score));

	m_gameOver = false;

	m_snake.reset();
	m_apple.spawn(m_snake.getSnakeBody());
}
