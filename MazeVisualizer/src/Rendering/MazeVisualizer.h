#pragma once
#include <queue>
#include <chrono>
#include "../Maze/IMazeObserver.h"
#include "Grid.h"

class Maze;

struct CellChange {
	Coords position;
	Cell newCell;
};

class MazeVisualizer : public IMazeObserver {
public:
	MazeVisualizer(Maze* maze, int cellWidth, int spacing);
	~MazeVisualizer() = default;
public:
	void onCellChange(const Coords& position) override;
	void onFill(const Cell& cell) override;

	void render(sf::RenderTarget& target);

	void setStepDelay(const std::chrono::microseconds& delay);
private:
	sf::Color getColor(const Cell& cell) const;
private:
	Maze* m_maze;
	Grid m_grid;
	std::queue<CellChange> m_changes;

	std::chrono::microseconds m_stepDelay;
};