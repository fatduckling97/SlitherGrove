#include "snake.hpp"
#include "loaders.hpp"

Snake::Snake() {};

Snake::Snake(int tileSize, int boardWidth, int boardHeight, float moveDelay) 
	: m_tileSize(tileSize)
	, m_boardWidth(boardWidth)
	, m_boardHeight(boardHeight)
	, m_moveDelay(moveDelay)
{
	// loading head snake textures
	loadTexture(m_snakeTexture.head.up, "src\\head_up.png");
	loadTexture(m_snakeTexture.head.down, "src\\head_down.png");
	loadTexture(m_snakeTexture.head.left, "src\\head_left.png");
	loadTexture(m_snakeTexture.head.right, "src\\head_right.png");

	// loading head eating snake textures 
	loadTexture(m_snakeTexture.headEat.up, "src\\head_eat_up.png");
	loadTexture(m_snakeTexture.headEat.down, "src\\head_eat_down.png");
	loadTexture(m_snakeTexture.headEat.left, "src\\head_eat_left.png");
	loadTexture(m_snakeTexture.headEat.right, "src\\head_eat_right.png");

	// loading body textures
	loadTexture(m_snakeTexture.body.up, "src\\body_up.png");
	loadTexture(m_snakeTexture.body.down, "src\\body_down.png");
	loadTexture(m_snakeTexture.body.left, "src\\body_left.png");
	loadTexture(m_snakeTexture.body.right, "src\\body_right.png");

	// loading body corner textures
	loadTexture(m_snakeTexture.bodyCorner.topLeft, "src\\body_corner_upleft.png");
	loadTexture(m_snakeTexture.bodyCorner.topRight, "src\\body_corner_upright.png");
	loadTexture(m_snakeTexture.bodyCorner.downLeft, "src\\body_corner_downleft.png");
	loadTexture(m_snakeTexture.bodyCorner.downRight, "src\\body_corner_downright.png");

	// loading tail textures
	loadTexture(m_snakeTexture.tail.up, "src\\tail_up.png");
	loadTexture(m_snakeTexture.tail.down, "src\\tail_down.png");
	loadTexture(m_snakeTexture.tail.left, "src\\tail_left.png");
	loadTexture(m_snakeTexture.tail.right, "src\\tail_right.png");

	m_snakeHeadSprite.emplace(m_snakeTexture.head.right);
	m_snakeHeadEatSprite.emplace(m_snakeTexture.headEat.right);
	m_snakeBodySprite.emplace(m_snakeTexture.body.right);
	m_snakeBodyCornerSprite.emplace(m_snakeTexture.bodyCorner.topRight);
	m_snakeTailSprite.emplace(m_snakeTexture.tail.right);

}

void Snake::changeDirection(sf::Keyboard::Key key) 
{
	switch (key) 
	{
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

sf::Vector2i Snake::getNextHeadPosition() const
{
	sf::Vector2i nextHead = getHeadPosition();

	switch (m_nextDirection)
	{
	case Direction::Up:
		nextHead.y--;
		break;

	case Direction::Down:
		nextHead.y++;
		break;

	case Direction::Left:
		nextHead.x--;
		break;

	case Direction::Right:
		nextHead.x++;
		break;
	}

	return nextHead;
}

void Snake::setEating(bool eating)
{
	m_isEating = eating;
}

void Snake::draw(sf::RenderWindow& window) 
{
	drawHead(window);

	for (size_t i = 1; i < m_snakeBody.size() - 1; i++)
	{
		drawBody(window, i);
	}

	drawTail(window);
}

void Snake::drawHead(sf::RenderWindow& window)
{
	if (m_isEating)
	{
		switch (m_currentDirection)
		{
			case Direction::Up:
				m_snakeHeadEatSprite->setTexture(m_snakeTexture.headEat.up);
				break;
			case Direction::Down:
				m_snakeHeadEatSprite->setTexture(m_snakeTexture.headEat.down);
				break;
			case Direction::Left:
				m_snakeHeadEatSprite->setTexture(m_snakeTexture.headEat.left);
				break;
			case Direction::Right:
				m_snakeHeadEatSprite->setTexture(m_snakeTexture.headEat.right);
				break;
		}

		m_snakeHeadEatSprite->setPosition(
			sf::Vector2f(
				static_cast<float>(m_snakeBody.front().x * m_tileSize),
				static_cast<float>(m_snakeBody.front().y * m_tileSize)
			)
		);

		window.draw(*m_snakeHeadEatSprite);
	}
	else
	{
		switch (m_currentDirection)
		{
			case Direction::Up:
				m_snakeHeadSprite->setTexture(m_snakeTexture.head.up);
				break;
			case Direction::Down:
				m_snakeHeadSprite->setTexture(m_snakeTexture.head.down);
				break;
			case Direction::Left:
				m_snakeHeadSprite->setTexture(m_snakeTexture.head.left);
				break;
			case Direction::Right:
				m_snakeHeadSprite->setTexture(m_snakeTexture.head.right);
				break;
		}

		m_snakeHeadSprite->setPosition(
			sf::Vector2f(
				static_cast<float>(m_snakeBody.front().x * m_tileSize),
				static_cast<float>(m_snakeBody.front().y * m_tileSize)
			)
		);

		window.draw(*m_snakeHeadSprite);
	}
}

void Snake::drawBody(sf::RenderWindow& window, size_t idx)
{
	const sf::Vector2i& current = m_snakeBody[idx];
	const sf::Vector2i& previous = m_snakeBody[idx - 1];
	const sf::Vector2i& next = m_snakeBody[idx + 1];

	sf::Vector2i toPrevious = previous - current;
	sf::Vector2i toNext = next - current;

	bool hasDown = (toPrevious.y == -1 || toNext.y == -1);
	bool hasUp = (toPrevious.y == 1 || toNext.y == 1);
	bool hasRight = (toPrevious.x == -1 || toNext.x == -1);
	bool hasLeft = (toPrevious.x == 1 || toNext.x == 1);

	if (previous.x == current.x && current.x == next.x)
	{
		if (previous.y > next.y)
		{
			m_snakeBodySprite->setTexture(m_snakeTexture.body.up);
		}
		else
		{
			m_snakeBodySprite->setTexture(m_snakeTexture.body.down);
		}

		m_snakeBodySprite->setPosition(
			sf::Vector2f(
				static_cast<float>(current.x * m_tileSize),
				static_cast<float>(current.y * m_tileSize)
			)
		);

		window.draw(*m_snakeBodySprite);
	}
	else if (previous.y == current.y && current.y == next.y)
	{
		if (previous.x > next.x)
		{
			m_snakeBodySprite->setTexture(m_snakeTexture.body.left);
		}
		else
		{
			m_snakeBodySprite->setTexture(m_snakeTexture.body.right);
		}

		m_snakeBodySprite->setPosition(
			sf::Vector2f(
				static_cast<float>(current.x * m_tileSize),
				static_cast<float>(current.y * m_tileSize)
			)
		);

		window.draw(*m_snakeBodySprite);
	}
	else
	{
		// corner body
		if (hasDown && hasLeft)
		{
			m_snakeBodyCornerSprite->setTexture(m_snakeTexture.bodyCorner.downLeft);
		}
		else if (hasDown && hasRight)
		{
			m_snakeBodyCornerSprite->setTexture(m_snakeTexture.bodyCorner.downRight);
		}
		else if (hasUp && hasLeft)
		{
			m_snakeBodyCornerSprite->setTexture(m_snakeTexture.bodyCorner.topLeft);
		}
		else if (hasUp && hasRight)
		{
			m_snakeBodyCornerSprite->setTexture(m_snakeTexture.bodyCorner.topRight);
		}

		m_snakeBodyCornerSprite->setPosition(
			sf::Vector2f(
				static_cast<float>(current.x * m_tileSize),
				static_cast<float>(current.y * m_tileSize)
			)
		);
		
		window.draw(*m_snakeBodyCornerSprite);
	}
}

void Snake::drawTail(sf::RenderWindow& window)
{
	const sf::Vector2i& tail = m_snakeBody.back();
	const sf::Vector2i& beforeTail = m_snakeBody[m_snakeBody.size() - 2];

	sf::Vector2i direction = tail - beforeTail;

	if (direction.x == -1)
	{
		m_snakeTailSprite->setTexture(m_snakeTexture.tail.right);
	}
	else if (direction.x == 1)
	{
		m_snakeTailSprite->setTexture(m_snakeTexture.tail.left);
	}
	else if (direction.y == -1)
	{
		m_snakeTailSprite->setTexture(m_snakeTexture.tail.down);
	}
	else if (direction.y == 1)
	{
		m_snakeTailSprite->setTexture(m_snakeTexture.tail.up);
	}

	m_snakeTailSprite->setPosition(
		sf::Vector2f(
			static_cast<float>(tail.x * m_tileSize),
			static_cast<float>(tail.y * m_tileSize)
		)
	);

	window.draw(*m_snakeTailSprite);
}

void Snake::update(sf::Time deltaTime) 
{
	if (!m_alive)
		return;

	m_moveTimer += deltaTime.asSeconds();

	if (m_moveTimer >= m_moveDelay) 
	{
		move();

		if (checkSelfCollision() || checkWallCollision()) {
			m_alive = false;
			return;
		}

		m_moveTimer -= m_moveDelay;
	}
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

	if (head.x <= 1 || head.x >= m_boardWidth - 2 || head.y <= 1 || head.y >= m_boardHeight - 2)
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

