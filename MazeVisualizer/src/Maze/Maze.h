#pragma once
#include <vector>
#include "../Util/Coords.h"
#include "../Util/Size.h"

enum class Cell {
	EMPTY,
	WALL
};

class IMazeObserver;

class Maze {
public:
	Maze(const Size& size);
	~Maze() = default;
public:
	void setCellAt(const Coords& position, const Cell& cell);
	Cell getCellAt(const Coords& position) const;

	void fill(const Cell& cell);

	Size getSize() const;

	bool isOutOfBounds(const Coords& position) const;

	void registerObserver(IMazeObserver* observer);
private:
	std::size_t getIndex(const Coords& position) const;
private:
	std::vector<Cell> m_cells;
	Size m_size;
	std::vector<IMazeObserver*> m_observers;
};