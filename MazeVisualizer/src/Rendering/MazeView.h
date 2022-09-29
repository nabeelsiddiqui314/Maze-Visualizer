#pragma once
#include <queue>
#include <chrono>
#include "../Maze/IMazeObserver.h"
#include "Grid.h"
#include "../Maze/Maze.h"

struct Animation {
	Coords position;
	sf::Color cellColor;
	sf::Color cursorColor;
	int stage = 0;
};

class MazeView : public IMazeObserver {
public:
	MazeView(Maze* maze, int cellWidth, int spacing);
	~MazeView() = default;
public:
	void onCellChange(const Coords& position) override;
	void onCellSearch(const Coords& position) override;
	void onFill(const Cell& cell) override;

	void render(sf::RenderTarget& target);

	void setStepDelay(const std::chrono::microseconds& delay);
private:
	sf::Color getCellColor(const Cell& cell) const;
	void enqueueAnimation(const Coords& position, const sf::Color& cellColor, const sf::Color& cursorColor);
private:
	Maze* m_maze;
	Grid m_grid;
	std::queue<Animation> m_animationQueue;

	std::chrono::microseconds m_stepDelay;
};