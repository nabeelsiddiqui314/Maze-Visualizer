#pragma once
#include <vector>
#include "../Util/Coords.h"

enum class Cell {
	EMPTY,
	WALL
};

class IMazeObserver;

class Maze {
public:
	Maze(int width, int height);
	~Maze() = default;
public:
	void setCellAt(const Coords& position, const Cell& cell);
	Cell getCellAt(const Coords& position) const;

	void registerObserver(IMazeObserver* observer);
private:
	std::size_t getIndex(const Coords& position) const;
private:
	std::vector<Cell> m_cells;
	int m_width;
	std::vector<IMazeObserver*> m_observers;
};