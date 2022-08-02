#include "Maze.h"
#include "IMazeObserver.h"
#include "../Algorithms/Generation/IMazeGenerator.h"

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

void Maze::fill(const Cell& cell) {
    std::fill(m_cells.begin(), m_cells.end(), cell);

    for (auto& observer : m_observers) {
        observer->onFill(cell);
    }
}

Size Maze::getSize() const {
    return m_size;
}

bool Maze::isOutOfBounds(const Coords& position) const {
    return position.x < 0 || position.x >= m_size.width || 
        position.y < 0 || position.y >= m_size.height;
}

void Maze::setGenerator(std::unique_ptr<IMazeGenerator> generator) {
    m_generator = std::move(generator);
}

void Maze::generate() {
    if (m_generator) {
        m_generator->generate(*this);
    }
}

void Maze::registerObserver(IMazeObserver* observer) {
    m_observers.push_back(observer);
}

std::size_t Maze::getIndex(const Coords& position) const {
    return position.x + position.y * m_size.width;
}
