#include <cstdlib>
#include "apple.hpp"
#include "TextureLoader.hpp"


Apple::Apple() {}

Apple::Apple(int tileSize, int boardWidth, int boardHeight)
	: m_tileSize(tileSize)
	, m_boardWidth(boardWidth)
	, m_boardHeight(boardHeight)
{
	loadTexture(m_appleTexture, "src\\apple.png");

	m_appleSprite.emplace(m_appleTexture);
}

void Apple::spawn(const std::vector<sf::Vector2i>& snakeBody)
{
	bool collision = false;

	do
	{
		collision = false;

		int x = rand() % (m_boardWidth - 2) + 1;
		int y = rand() % (m_boardHeight - 2) + 1;

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
	m_appleSprite->setPosition(
		sf::Vector2f(
			static_cast<float>(m_applePosition.x * m_tileSize),
			static_cast<float>(m_applePosition.y * m_tileSize)
		)
	);

	window.draw(*m_appleSprite);
}

sf::Vector2i Apple::getApplePosition() const
{
	return m_applePosition;
}