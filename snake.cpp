#include "snake.hpp"

Snake::Snake() {};

Snake::Snake(int tileSize, int boardWidth, int boardHeight, float moveDelay) 
	: m_tileSize(tileSize)
	, m_boardWidth(boardWidth)
	, m_boardHeight(boardHeight)
	, m_moveDelay(moveDelay)
{
	m_snakeBodyShape.setFillColor(sf::Color::Green);
	m_snakeBodyShape.setSize(
		sf::Vector2f(
			static_cast<float>(m_tileSize),
			static_cast<float>(m_tileSize)
		)
	);
}

void Snake::changeDirection(sf::Keyboard::Key key) 
{
	switch (key) {
		case sf::Keyboard::Key::Up:
			if (m_currentDirection != Direction::Down)
				m_nextDirection = Direction::Up;
			break;
		case sf::Keyboard::Key::Down:
			if (m_currentDirection != Direction::Up)
				m_nextDirection = Direction::Down;
			break;
		case sf::Keyboard::Key::Left:
			if (m_currentDirection != Direction::Right)
				m_nextDirection = Direction::Left;
			break;
		case sf::Keyboard::Key::Right:
			if (m_currentDirection != Direction::Left)
				m_nextDirection = Direction::Right;
			break;
		default:
			break;
	}
}

void Snake::move() 
{
	m_currentDirection = m_nextDirection;
	sf::Vector2i newHeadPosition= getHeadPosition();

	switch (m_nextDirection)
	{
		case Direction::Up:
			newHeadPosition.y--;
			break;
		case Direction::Down:
			newHeadPosition.y++;
			break;
		case Direction::Left:
			newHeadPosition.x--;
			break;
		case Direction::Right:
			newHeadPosition.x++;
			break;
		default:
			break;
	}

	m_snakeBody.insert(m_snakeBody.begin(), newHeadPosition);

	if (m_shouldGrow)
	{
		m_shouldGrow = false;
	}
	else 
	{
		m_snakeBody.pop_back();
	}

}

void Snake::grow() 
{
	m_shouldGrow = true;
}

void Snake::draw(sf::RenderWindow& window) 
{
	for (const auto& segment : m_snakeBody) {
		m_snakeBodyShape.setPosition(
			sf::Vector2f(
				static_cast<float>(segment.x * m_tileSize), 
				static_cast<float>(segment.y * m_tileSize)
			)
		);

		window.draw(m_snakeBodyShape);
	}
}

void Snake::update(sf::Time deltaTime) 
{
	if (!m_alive)
		return;

	m_moveTimer += deltaTime.asSeconds();

	if (m_moveTimer >= m_moveDelay) {
		move();
		if (checkSelfCollision() || checkWallCollision()) {
			m_alive = false;
		}
		m_moveTimer -= m_moveDelay;
	}

	std::cout << m_moveTimer << " / " << m_moveDelay << '\n';
}

void Snake::reset() 
{
	m_currentDirection = Direction::Right; 
	m_nextDirection = Direction::Right;
	
	m_moveTimer = 0.0f;

	m_alive = true;

	m_snakeBody = {
		sf::Vector2i(m_boardWidth / 2, m_boardHeight / 2), 
		sf::Vector2i(m_boardWidth / 2 - 1, m_boardHeight /2), 
		sf::Vector2i(m_boardWidth / 2 - 2, m_boardHeight / 2)
	};
}

bool Snake::checkSelfCollision() const 
{
	sf::Vector2i head = getHeadPosition();

	for (size_t i = 1; i < m_snakeBody.size(); i++) {
		if (head == m_snakeBody[i])
			return true;
	}

	return false;
}

bool Snake::checkWallCollision() const 
{
	sf::Vector2i head = getHeadPosition();

	if (head.x < 0 || head.x >= m_boardWidth || head.y < 0 || head.y >=m_boardHeight)
		return true;

	return false;
}

bool Snake::isAlive() const
{
	return m_alive;
}

sf::Vector2i Snake::getHeadPosition() const
{
	return m_snakeBody.front();
}

const std::vector<sf::Vector2i>& Snake::getSnakeBody() const
{
	return m_snakeBody;
}

sf::Vector2i Snake::getTailPosition() const
{
	return m_snakeBody.back();
}

size_t Snake::getLength() const
{
	return m_snakeBody.size();
}

