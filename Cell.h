#pragma once
#include <SFML/Graphics.hpp>

class Cell
{
public:
	void draw(sf::RenderWindow& window,  int x, int y);
	void change_color(sf::RenderWindow& window, sf::Color color);
	int m_row = 0, m_column = 0;
	bool wall = true;
	bool visited = false;
private:
	sf::RectangleShape m_cell;
};

