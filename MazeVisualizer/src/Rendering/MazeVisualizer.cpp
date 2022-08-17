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

	setCellColor(position, cursorColor, true);
	setCellColor(position, cellColor, false);
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
	if (!m_changes.empty()) {
		auto change = m_changes.front();
		m_changes.pop();

		m_grid.setCellColor(change.position, change.color);

		if (!change.showStep) {
			std::this_thread::sleep_for(m_stepDelay);
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

void MazeVisualizer::setCellColor(const Coords& position, const sf::Color& color, bool showStep) {
	m_changes.push({ position, color, showStep });
}