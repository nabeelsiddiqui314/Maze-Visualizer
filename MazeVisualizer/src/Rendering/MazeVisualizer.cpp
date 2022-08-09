#include "MazeVisualizer.h"
#include "../Maze/Maze.h"

MazeVisualizer::MazeVisualizer(Maze* maze, int cellWidth, int spacing) 
	: m_maze(maze), m_grid(maze->getSize(), cellWidth, spacing) {}

void MazeVisualizer::onCellChange(const Coords& position) {
	Cell modifiedCell = m_maze->getCellAt(position);
	m_grid.setCellColor(position, getColor(modifiedCell));
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
	m_grid.render(target);
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
