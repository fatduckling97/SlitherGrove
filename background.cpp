#include "background.hpp"
#include "TextureLoader.hpp"
#include <iostream>


Background::Background(int tileSize, int boardWidth, int boardHeight)
	: m_tileSize(tileSize)
	, m_boardWidth(boardWidth)
	, m_boardHeight(boardHeight)
{
	// Loading edge grass textures
	loadTexture(m_edgeTopTexture, "src\\edge_top.png");
	loadTexture(m_edgeLeftTexture, "src\\edge_left.png");
	loadTexture(m_edgeRightTexture, "src\\edge_right.png");
	loadTexture(m_edgeDownTexture, "src\\edge_down.png");
	loadTexture(m_edgeCornerTexture, "src\\edge_corner.png");
	loadTexture(m_grassTexture, "src\\grass.png");

	m_edgeTopSprite.emplace(m_edgeTopTexture);
	m_edgeDownSprite.emplace(m_edgeDownTexture);
	m_edgeLeftSprite.emplace(m_edgeLeftTexture);
	m_edgeRightSprite.emplace(m_edgeRightTexture);
	m_edgeCornerSprite.emplace(m_edgeCornerTexture);
	m_grassSprite.emplace(m_grassTexture);
}

void Background::draw(sf::RenderWindow& window)
{
	

	for (int y = 0; y < m_boardHeight; y++)
	{
		for (int x = 0; x < m_boardWidth; x++)
		{
			if ((x == 0 && y == 0) || 
				(x == m_boardWidth - 1 && y == 0) ||
				(x == 0 && y == m_boardHeight - 1) ||
				(x == m_boardWidth - 1 && y == m_boardHeight - 1))
			{
				m_edgeCornerSprite->setPosition(
					sf::Vector2f(
						static_cast<float>(x * m_tileSize), 
						static_cast<float>(y * m_tileSize)
					)
				);

				window.draw(*m_edgeCornerSprite);
			}

			else if (y == 0)
			{
				m_edgeTopSprite->setPosition(
					sf::Vector2f(
						static_cast<float>(x * m_tileSize),
						static_cast<float>(y * m_tileSize)
					)
				);

				window.draw(*m_edgeTopSprite);
			}

			else if (y == m_boardHeight - 1)
			{
				m_edgeDownSprite->setPosition(
					sf::Vector2f(
						static_cast<float>(x * m_tileSize),
						static_cast<float>(y * m_tileSize)
					)
				);

				window.draw(*m_edgeDownSprite);
			}

			else if (x == 0)
			{
				m_edgeLeftSprite->setPosition(
					sf::Vector2f(
						static_cast<float>(x * m_tileSize),
						static_cast<float>(y * m_tileSize)
					)
				);

				window.draw(*m_edgeLeftSprite);
			}

			else if (x == m_boardWidth - 1)
			{
				m_edgeRightSprite->setPosition(
					sf::Vector2f(
						static_cast<float>(x * m_tileSize),
						static_cast<float>(y * m_tileSize)
					)
				);

				window.draw(*m_edgeRightSprite);
			}

			else
			{
				m_grassSprite->setPosition(
					sf::Vector2f(
						static_cast<float>(x * m_tileSize),
						static_cast<float>(y * m_tileSize)
					)
				);
				window.draw(*m_grassSprite);
			}
		}
	}
}
