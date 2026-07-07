#include <cstdlib>
#include "apple.hpp"


Apple::Apple() {}

Apple::Apple(int tileSize, int boardWidth, int boardHeight)
	: m_tileSize(tileSize)
	, m_boardWidth(boardWidth)
	, m_boardHeight(boardHeight)
{

}

void Apple::spawn(const std::vector<sf::Vector2i>& snakeBody)
{
	bool collision = false;

	do
	{
		int x = rand() % m_boardWidth;
		int y = rand() % m_boardHeight;

		m_applePosition = sf::Vector2i(x, y);

		for (const auto& segment : snakeBody)
		{
			if (segment == m_applePosition)
			{
				collision = true;
				break;
			}
		}
	} while (collision);
}

void Apple::draw(sf::RenderWindow& window)
{
	m_appleShape.setFillColor(sf::Color::Red);
	m_appleShape.setPosition(
		sf::Vector2f(
			static_cast<float>(m_applePosition.x * m_tileSize),
			static_cast<float>(m_applePosition.y * m_tileSize)
		)
	);
	m_appleShape.setSize(
		sf::Vector2f(
			static_cast<float>(m_tileSize),
			static_cast<float>(m_tileSize)
		)
	);

	window.draw(m_appleShape);
}

sf::Vector2i Apple::getApplePosition() const
{
	return m_applePosition;
}