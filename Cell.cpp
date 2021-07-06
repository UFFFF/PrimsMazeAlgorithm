#include "Cell.h"

void Cell::draw(sf::RenderWindow& window, int x, int y)
{
	m_cell.setFillColor(sf::Color::White);
	m_cell.setSize(sf::Vector2f(10, 10));
	m_cell.setPosition(sf::Vector2f(10 * x, 10 * y));
	window.draw(m_cell);
}

void Cell::change_color(sf::RenderWindow& window, sf::Color color)
{
	m_cell.setFillColor(color);
	window.draw(m_cell);
}
