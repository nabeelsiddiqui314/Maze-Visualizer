#include "MazeView.h"
#include <thread>
#include "../Rendering/Colors.h"

using namespace std::chrono_literals;

MazeView::MazeView(Maze* maze, int cellWidth, int spacing) 
	: sfg::Canvas(false), m_maze(maze), m_grid(maze->getSize(), cellWidth, spacing), m_stepDelay(5us) {
	SetRequisition(m_grid.getSize());
}

MazeView::Ptr MazeView::Create(Maze* maze, int cellWidth, int spacing) {
	return Ptr(new MazeView(maze, cellWidth, spacing));
}

void MazeView::onCellChange(const Coords& position) {
	Cell newCell = m_maze->getCellAt(position);
	sf::Color cellColor = getCellColor(newCell);

	switch (m_maze->getState()) {
	case Maze::State::IDLE:
		m_grid.setCellColor(position, cellColor);
		break;
	case Maze::State::GENERATING:
		enqueueAnimation(position, cellColor, Colors::GenerationCursor);
		break;
	case Maze::State::PATHFINDING:
		enqueueAnimation(position, cellColor, Colors::PathCursor);
		break;
	}
}

void MazeView::onCellSearch(const Coords& position) {
	if (m_maze->getState() == Maze::State::PATHFINDING) {
		if (m_grid.getCellColor(position) != Colors::Wall) {
			enqueueAnimation(position, Colors::SearchArea, Colors::SearchCursor);
		}
	}
}

void MazeView::onFill(const Cell& cell) {
	const Size& size = m_maze->getSize();
	
	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {
			m_grid.setCellColor({x, y}, getCellColor(cell));
		}
	}
}

void MazeView::update() {
	addOverlay(m_maze->getPathStart(), Colors::PathStart);
	addOverlay(m_maze->getPathDestination(), Colors::PathEnd);
}

void MazeView::render() {
	if (!m_animationQueue.empty()) {
		auto& animation = m_animationQueue.front();

		// if the color is already set to what is desired then don't bother with the animation
		if (m_grid.getCellColor(animation.position) == animation.cellColor) {
			m_animationQueue.pop();
		}
		else {
			if (animation.stage == 0) {
				m_grid.setCellColor(animation.position, animation.cursorColor);
				animation.stage++;
			}
			else {
				std::this_thread::sleep_for(m_stepDelay);
				m_grid.setCellColor(animation.position, animation.cellColor);
				m_animationQueue.pop();
			}
		}
	}

	for (auto& overlay : m_overlays) {
		m_grid.setCellColor(overlay.position, overlay.overlayColor);
	}

	renderToCanvas();

	for (auto& overlay : m_overlays) {
		m_grid.setCellColor(overlay.position, overlay.originalColor);
	}
	m_overlays.clear();
}

void MazeView::setStepDelay(const std::chrono::microseconds& delay) {
	m_stepDelay = delay;
}

void MazeView::HandleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) {
	if (!IsMouseInWidget() || !press)
		return;

	auto allocation = GetAllocation();

	x -= allocation.left;
	y -= allocation.top;

	x /= m_grid.getCellWidth();
	y /= m_grid.getCellWidth();

	if (button == sf::Mouse::Left) {
		m_maze->setCellAt({ x, y }, Cell::WALL);
	}
	else {
		m_maze->setCellAt({ x, y }, Cell::EMPTY);
	}
}

sf::Color MazeView::getCellColor(const Cell& cell) const {
	sf::Color color;

	switch (cell) {
	case Cell::EMPTY:
		color = Colors::Empty;
		break;
	case Cell::WALL:
		color = Colors::Wall;
		break;
	case Cell::PATH:
		color = Colors::Path;
		break;
	}

	return color;
}

void MazeView::enqueueAnimation(const Coords& position, const sf::Color& cellColor, const sf::Color& cursorColor) {
	m_animationQueue.push({ position, cellColor, cursorColor });
}

void MazeView::addOverlay(const Coords& position, const sf::Color& color) {
	sf::Color originalColor = m_grid.getCellColor(position);
	m_overlays.push_back({ position, color, originalColor });
}

void MazeView::renderToCanvas() {
	Bind();
	Clear();
	Draw(m_grid);
	Display();
	Unbind();
}