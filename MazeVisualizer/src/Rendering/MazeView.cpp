#include "MazeView.h"
#include <thread>
#include "Colors.h"

using namespace std::chrono_literals;

MazeView::MazeView(Maze* maze, int cellWidth, int spacing) 
	: m_maze(maze), m_grid(maze->getSize(), cellWidth, spacing), m_stepDelay(5us) {}

void MazeView::onCellChange(const Coords& position) {
	Cell newCell = m_maze->getCellAt(position);
	sf::Color cellColor = getCellColor(newCell);

	switch (m_maze->getState()) {
	case State::IDLE:
		m_grid.setCellColor(position, cellColor);
		break;
	case State::GENERATING:
		enqueueAnimation(position, cellColor, Colors::GenerationCursor);
		break;
	case State::PATHFINDING:
		enqueueAnimation(position, cellColor, Colors::PathCursor);
		break;
	}
}

void MazeView::onCellSearch(const Coords& position) {
	if (m_maze->getState() == State::PATHFINDING) {
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

void MazeView::setPosition(const sf::Vector2f& positon) {
	m_grid.setPosition(positon);
}

sf::Vector2f MazeView::getPosition() const {
	return m_grid.getPosition();
}

void MazeView::update() {
	addOverlay(m_maze->getPathStart(), Colors::PathStart);
	addOverlay(m_maze->getPathDestination(), Colors::PathEnd);
}

void MazeView::render(sf::RenderTarget& target) {
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

	m_grid.render(target);

	for (auto& overlay : m_overlays) {
		m_grid.setCellColor(overlay.position, overlay.originalColor);
	}
	m_overlays.clear();
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