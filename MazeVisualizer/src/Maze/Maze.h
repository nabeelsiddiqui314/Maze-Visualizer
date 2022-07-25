#pragma once
#include <vector>
#include <memory>
#include "../Util/Coords.h"

enum class Cell {
	EMPTY,
	WALL
};

class IMazeObserver;

class Maze {
	using ObserverPtr = std::weak_ptr<IMazeObserver>;
public:
	Maze(int width, int height);
	~Maze() = default;
public:
	void setCellAt(const Coords& position, const Cell& cell);
	Cell getCellAt(const Coords& position) const;

	void registerObserver(const ObserverPtr& observer);
private:
	std::size_t getIndex(const Coords& position) const;
private:
	std::vector<Cell> m_cells;
	int m_width;
	std::vector<ObserverPtr> m_observers;
};