#pragma once
#include <vector>
#include <memory>
#include "../Util/Array2D.h"
#include "../Algorithms/Generation/IMazeGenerator.h"
#include "../Algorithms/Pathfinding/IPathfinder.h"

enum class Cell {
	EMPTY,
	WALL,
	PATH
};

class IMazeObserver;

class Maze {
private:
	using ObserverPtr = std::weak_ptr<IMazeObserver>;
public:
	enum class State {
		IDLE,
		GENERATING,
		PATHFINDING
	};
public:
	Maze(const Size& size);
	~Maze() = default;
public:
	void setCellAt(const Coords& position, const Cell& cell);
	Cell getCellAt(const Coords& position) const;

	void fill(const Cell& cell);

	Size getSize() const;

	bool isOutOfBounds(const Coords& position) const;

	void setGenerator(std::unique_ptr<IMazeGenerator> generator);
	void generate();

	void setPathStart(const Coords& position);
	void setPathDestination(const Coords& position);

	void randomizePathEnds();

	Coords getPathStart() const;
	Coords getPathDestination() const;

	void setPathfinder(std::unique_ptr<IPathFinder> pathfinder);
	void findPath();

	State getState() const;

	void registerObserver(const ObserverPtr& observer);
private:
	Array2D<Cell> m_cells;
	Size m_size;
	std::unique_ptr<IMazeGenerator> m_generator;
	Coords m_start, m_end;
	std::unique_ptr<IPathFinder> m_pathfinder;
	std::vector<ObserverPtr> m_observers;
	State m_state;
};