#pragma once
#include <queue>
#include <vector>
#include <chrono>
#include "../Maze/IMazeObserver.h"
#include "../Rendering/Grid.h"
#include "../Maze/Maze.h"
#include <SFGUI/Widgets.hpp>

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

class MazeView : public IMazeObserver, public sfg::Canvas {
public:
	using Ptr = std::shared_ptr<MazeView>;
public:
	~MazeView() = default;
private:
	MazeView(Maze* maze, int cellWidth, int spacing);
public:
	static Ptr Create(Maze* maze, int cellWidth, int spacing);

	void onCellChange(const Coords& position) override;
	void onCellSearch(const Coords& position) override;
	void onFill(const Cell& cell) override;

	Coords getCellFromPoint(const sf::Vector2i& point) const;

	void update();
	void render();

	void setStepDelay(const std::chrono::microseconds& delay);
private:
	void HandleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) override;

	sf::Color getCellColor(const Cell& cell) const;
	void enqueueAnimation(const Coords& position, const sf::Color& cellColor, const sf::Color& cursorColor);
	void addOverlay(const Coords& position, const sf::Color& color);

	void renderToCanvas();
private:
	Maze* m_maze;
	Grid m_grid;
	std::queue<Animation> m_animationQueue;
	std::vector<Overlay> m_overlays;

	std::chrono::microseconds m_stepDelay;
};