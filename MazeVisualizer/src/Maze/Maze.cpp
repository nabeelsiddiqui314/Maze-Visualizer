#include "Maze.h"

Maze::Maze(int width, int height) 
    : m_cells(width * height), 
      m_width(width) {}

void Maze::setCellAt(const sf::Vector2i& position, const Cell& cell) {
    m_cells[getIndex(position)] = cell;
}

Cell Maze::getCellAt(const sf::Vector2i& position) const {
    return m_cells[getIndex(position)];
}

std::size_t Maze::getIndex(const sf::Vector2i& position) const {
    return std::size_t();
}
