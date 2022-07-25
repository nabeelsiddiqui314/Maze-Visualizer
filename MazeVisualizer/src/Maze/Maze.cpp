#include "Maze.h"
#include "IMazeObserver.h"

Maze::Maze(const Size& size) 
    : m_cells(size.width * size.height, Cell::EMPTY), 
      m_size(size) {}

void Maze::setCellAt(const Coords& position, const Cell& cell) {
    m_cells[getIndex(position)] = cell;

    for (auto& observer : m_observers) {
        observer->onCellChange(position);
    }
}

Cell Maze::getCellAt(const Coords& position) const {
    return m_cells[getIndex(position)];
}

void Maze::registerObserver(IMazeObserver* observer) {
    m_observers.push_back(observer);
}

std::size_t Maze::getIndex(const Coords& position) const {
    return position.x + position.y * m_size.width;
}
