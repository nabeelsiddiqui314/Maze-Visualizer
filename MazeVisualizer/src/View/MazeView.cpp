#include "MazeView.h"
#include <thread>
#include "../Rendering/Colors.h"

using namespace std::chrono_literals;

MazeView::MazeView(Maze* maze, int cellWidth, int spacing) 
	: m_maze(maze), m_grid(maze->getSize(), cellWidth, spacing), m_stepDelay(5us), m_canvas(sfg::Canvas::Create()) {
	m_canvas->SetRequisition(m_grid.getSize());
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

Coords MazeView::getCellFromPoint(const sf::Vector2i& point) const {
	auto canvasAllocation = m_canvas->GetAllocation();

	sf::Vector2i gridPosition(canvasAllocation.left, canvasAllocation.top);
	sf::Vector2i difference = point - gridPosition;

	int totalWidth = m_grid.getCellWidth() + m_grid.getSpacing();

	return { difference.x / totalWidth, difference.y / totalWidth };
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

sfg::Canvas::Ptr MazeView::getCanvas() const {
	return m_canvas;
}

void MazeView::setStepDelay(const std::chrono::microseconds& delay) {
	m_stepDelay = delay;
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
	m_canvas->Bind();
	m_canvas->Clear();
	m_canvas->Draw(m_grid);
	m_canvas->Display();
	m_canvas->Unbind();
}