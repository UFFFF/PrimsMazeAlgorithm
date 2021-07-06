#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <optional>
#include "Cell.h"

class point {
public:
	point(int row, int column) {
		x = row;
		y = column;
	}
	point() = default;
	int x = 0, y = 0;
};

class Field
{
public:
	Field();
	void draw(sf::RenderWindow& window);
	void prims_alg(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
private:
	bool in_bounds(int row, int column);
	std::optional<point> is_wall_visited_w(int row, int column);
	std::optional<point> is_wall_visited_s(int row, int column);
	void add_walls(int row, int column);
	int rnd_number(int s);
	std::vector<std::vector<Cell>> m_field;
	std::vector<point> w_list;
};

