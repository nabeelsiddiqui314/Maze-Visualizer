#include "MazeVisualizer.h"
#include "../Maze/Maze.h"

MazeVisualizer::MazeVisualizer(Maze* maze, int cellWidth, int spacing) 
	: m_maze(maze), m_grid(maze->getSize(), cellWidth, spacing) {}

void MazeVisualizer::onCellChange(const Coords& position) {
	Cell modifiedCell = m_maze->getCellAt(position);
	switch (modifiedCell) {
	case Cell::EMPTY:
		m_grid.setCellColor(position, sf::Color::White);
		break;
	case Cell::WALL:
		m_grid.setCellColor(position, sf::Color::Black);
		break;
	}
}

void MazeVisualizer::render(sf::RenderTarget& target) {
	m_grid.render(target);
}