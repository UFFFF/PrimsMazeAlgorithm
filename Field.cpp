#include "Field.h"

Field::Field()
{
	m_field.resize(100);

	for (auto& e : m_field) {
		e.resize(100);
	}
}

void Field::draw(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < m_field.size(); i++) {
		for (unsigned int j = 0; j < m_field.at(i).size(); j++) {
			m_field.at(i).at(j).draw(window, i, j);
			m_field.at(i).at(j).m_row = i;
			m_field.at(i).at(j).m_column = j;
		}
	}
}

void Field::prims_alg(sf::RenderWindow& window)
{
	int rnd_row = rnd_number(m_field.size() - 1);
	int rnd_column = rnd_number(m_field.front().size() - 1);
	m_field.at(rnd_row).at(rnd_column).wall = false;
	m_field.at(rnd_row).at(rnd_column).visited = true;
	int start_row = m_field.at(rnd_row).at(rnd_column).m_row;
	int start_column = m_field.at(rnd_row).at(rnd_column).m_column;
	add_walls(start_row, start_column);

	while (!w_list.empty()) {
		int c_n = rnd_number(w_list.size() - 1);
		point a_p = w_list.at(c_n);
		int a_row = m_field.at(a_p.x).at(a_p.y).m_row;
		int a_column = m_field.at(a_p.x).at(a_p.y).m_column;
		if (auto u_c = is_wall_visited_w(a_row, a_column)) {
			m_field.at(u_c->x).at(u_c->y).visited = true;
			m_field.at(u_c->x).at(u_c->y).wall = false;
			m_field.at(a_p.x).at(a_p.y).wall = false;
			//add_walls(a_row, a_column);
			add_walls(u_c->x, u_c->y);
		}
		if(auto u_c = is_wall_visited_s(a_row, a_column)) {
			m_field.at(u_c->x).at(u_c->y).visited = true;
			m_field.at(u_c->x).at(u_c->y).wall = false;
			m_field.at(a_p.x).at(a_p.y).wall = false;
			//add_walls(a_row, a_column);
			add_walls(u_c->x, u_c->y);
		}

		w_list.erase(w_list.begin() + c_n);
		m_field.at(a_p.x).at(a_p.y).visited = true;

		update(window);
		window.display();
	}
}

void Field::update(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < m_field.size(); i++) {
		for (unsigned int j = 0; j < m_field.at(i).size(); j++) {
			if (!m_field.at(i).at(j).wall) {
				m_field.at(i).at(j).change_color(window, sf::Color::White);
			}
			else {
				m_field.at(i).at(j).change_color(window, sf::Color::Black);
			}
		}
	}
}

bool Field::in_bounds(int row, int column)
{
	return row < m_field.size() && column < m_field.front().size()
		&& row >= 0 && column >= 0;
}

std::optional<point> Field::is_wall_visited_w(int row, int column)
{
	if (in_bounds(row + 1, column) && m_field.at(row + 1).at(column).visited &&
		in_bounds(row - 1, column) && !m_field.at(row - 1).at(column).visited) {
		return point(row - 1, column);
	}
	else if (in_bounds(row - 1, column) && m_field.at(row - 1).at(column).visited &&
		in_bounds(row + 1, column) && !m_field.at(row + 1).at(column).visited) {
		return point(row + 1, column);
	}
	return {};
}

std::optional<point> Field::is_wall_visited_s(int row, int column)
{
	if (in_bounds(row, column + 1) && m_field.at(row).at(column + 1).visited && 
		in_bounds(row, column -1) && !m_field.at(row).at(column - 1).visited) {
		return point(row, column - 1);
	}
	else if (in_bounds(row, column - 1) && m_field.at(row).at(column - 1).visited && 
		in_bounds(row, column + 1) && !m_field.at(row).at(column + 1).visited) {
		return point(row, column + 1);
	}
	return {};
}

void Field::add_walls(int row, int column)
{
	if (in_bounds(row + 1, column) && m_field.at(row + 1).at(column).wall) {
		//m_field.at(row + 1).at(column).visited = true;
		w_list.push_back(point(row +1 , column));
	}
	if (in_bounds(row - 1, column) && m_field.at(row - 1).at(column).wall) {
		//m_field.at(row - 1).at(column).visited = true;
		w_list.push_back(point(row - 1, column));
	}
	if (in_bounds(row, column + 1) && m_field.at(row).at(column + 1).wall) {
		//m_field.at(row).at(column + 1).visited = true;
		w_list.push_back(point(row, column + 1));
	}
	if (in_bounds(row, column - 1) && m_field.at(row).at(column - 1).wall) {
		//m_field.at(row).at(column - 1).visited = true;
		w_list.push_back(point(row, column - 1));
	}
}

int Field::rnd_number(int s)
{
	int n = 0;

	std::random_device dev;
	std::mt19937 genr(dev());
	std::uniform_int_distribution<int> dis(0, s);

	n = dis(dev);

	return n;
}
