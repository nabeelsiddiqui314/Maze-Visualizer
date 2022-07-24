#include "Maze.h"

Maze::Maze(int width, int height) 
    : m_cells(width * height), 
      m_width(width) {}

void Maze::setCellAt(const Coords& position, const Cell& cell) {
    m_cells[getIndex(position)] = cell;
}

Cell Maze::getCellAt(const Coords& position) const {
    return m_cells[getIndex(position)];
}

std::size_t Maze::getIndex(const Coords& position) const {
    return position.x + position.y * m_width;
}
