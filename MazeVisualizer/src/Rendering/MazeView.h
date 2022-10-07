#pragma once
#include <queue>
#include <vector>
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

struct Overlay {
	Coords position;
	sf::Color overlayColor;
	sf::Color originalColor;
};

class MazeView : public IMazeObserver {
public:
	MazeView(Maze* maze, int cellWidth, int spacing);
	~MazeView() = default;
public:
	void onCellChange(const Coords& position) override;
	void onCellSearch(const Coords& position) override;
	void onFill(const Cell& cell) override;

	void setPosition(const sf::Vector2f& positon);
	Coords getCellFromPoint(const sf::Vector2i& point) const;

	void update();
	void render(sf::RenderTarget& target);

	void setStepDelay(const std::chrono::microseconds& delay);
private:
	sf::Color getCellColor(const Cell& cell) const;
	void enqueueAnimation(const Coords& position, const sf::Color& cellColor, const sf::Color& cursorColor);
	void addOverlay(const Coords& position, const sf::Color& color);
private:
	Maze* m_maze;
	Grid m_grid;
	std::queue<Animation> m_animationQueue;
	std::vector<Overlay> m_overlays;

	std::chrono::microseconds m_stepDelay;
};