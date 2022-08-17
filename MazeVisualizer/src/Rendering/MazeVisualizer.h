#pragma once
#include <queue>
#include <chrono>
#include "../Maze/IMazeObserver.h"
#include "Grid.h"
#include "../Maze/Maze.h"

struct ColorChange {
	Coords position;
	sf::Color color;
	bool showStep;
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
	sf::Color getCursorColor(const State& state) const;
	void setCellColor(const Coords& position, const sf::Color& color, bool showStep);
private:
	Maze* m_maze;
	Grid m_grid;
	std::queue<ColorChange> m_changes;

	std::chrono::microseconds m_stepDelay;
};