#include "Maze.h"
#include "IMazeObserver.h"

Maze::Maze(int width, int height) 
    : m_cells(width * height, Cell::EMPTY), 
      m_width(width) {}

void Maze::setCellAt(const Coords& position, const Cell& cell) {
    m_cells[getIndex(position)] = cell;

    for (auto& observerPtr : m_observers) {
        if (auto observer = observerPtr.lock()) {
            observer->onCellChange(position);
        }
    }
}

Cell Maze::getCellAt(const Coords& position) const {
    return m_cells[getIndex(position)];
}

void Maze::registerObserver(const ObserverPtr& observer) {
    m_observers.push_back(observer);
}

std::size_t Maze::getIndex(const Coords& position) const {
    return position.x + position.y * m_width;
}
