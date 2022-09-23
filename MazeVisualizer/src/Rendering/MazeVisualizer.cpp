#include "MazeVisualizer.h"
#include <thread>

using namespace std::chrono_literals;

MazeVisualizer::MazeVisualizer(Maze* maze, int cellWidth, int spacing) 
	: m_maze(maze), m_grid(maze->getSize(), cellWidth, spacing), m_stepDelay(5us) {}

void MazeVisualizer::onCellChange(const Coords& position) {
	Cell newCell = m_maze->getCellAt(position);
	sf::Color cellColor = getColor(newCell);

	// directly set color if no algorithm is being executed
	if (m_maze->getState() == State::IDLE) {
		m_grid.setCellColor(position, cellColor);
		return;
	}

	sf::Color cursorColor = getCursorColor(m_maze->getState());

	enqueueAnimation(position, cellColor, cursorColor);
}

void MazeVisualizer::onCellSearch(const Coords& position) {
	if (m_maze->getState() == State::PATHFINDING) {
		if (m_grid.getCellColor(position) != getColor(Cell::WALL)) {
			enqueueAnimation(position, sf::Color(20, 184, 128), sf::Color(213, 163, 20));
		}
	}
}

void MazeVisualizer::onFill(const Cell& cell) {
	const Size& size = m_maze->getSize();
	
	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {
			m_grid.setCellColor({x, y}, getColor(cell));
		}
	}
}

void MazeVisualizer::render(sf::RenderTarget& target) {
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

	m_grid.render(target);
}

void MazeVisualizer::setStepDelay(const std::chrono::microseconds& delay) {
	m_stepDelay = delay;
}

sf::Color MazeVisualizer::getColor(const Cell& cell) const {
	sf::Color color;

	switch (cell) {
	case Cell::EMPTY:
		color = sf::Color::White;
		break;
	case Cell::WALL:
		color =  sf::Color::Black;
		break;
	case Cell::PATH:
		color = sf::Color::Yellow;
		break;
	}

	return color;
}

sf::Color MazeVisualizer::getCursorColor(const State& state) const {
	sf::Color color;

	switch (m_maze->getState()) {
	case State::GENERATING:
		color = sf::Color::Red;
		break;
	case State::PATHFINDING:
		color = sf::Color::Green;
		break;
	}

	return color;
}

void MazeVisualizer::enqueueAnimation(const Coords& position, const sf::Color& cellColor, const sf::Color& cursorColor) {
	m_animationQueue.push({ position, cellColor, cursorColor });
}