#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

enum class Cell {
	EMPTY,
	WALL
};

class Maze {
public:
	Maze(int width, int height);
	~Maze() = default;
public:
	void setCellAt(const sf::Vector2i& position, const Cell& cell);
	Cell getCellAt(const sf::Vector2i& position) const;
private:
	std::size_t getIndex(const sf::Vector2i& position) const;
private:
	std::vector<Cell> m_cells;
	int m_width;
};