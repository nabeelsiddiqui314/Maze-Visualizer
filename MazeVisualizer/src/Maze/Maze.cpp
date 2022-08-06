#include "Maze.h"
#include "IMazeObserver.h"
#include "../Algorithms/Generation/IMazeGenerator.h"
#include "../Util/Random.h"

Maze::Maze(const Size& size) 
    : m_cells(size, Cell::EMPTY), 
      m_size(size),
      m_start(Random::get(size.width), Random::get(size.height)),
      m_end(Random::get(size.width), Random::get(size.height)) {}

void Maze::setCellAt(const Coords& position, const Cell& cell) {
    m_cells[position] = cell;

    for (auto& observer : m_observers) {
        observer->onCellChange(position);
    }
}

Cell Maze::getCellAt(const Coords& position) const {
    return m_cells[position];
}

void Maze::fill(const Cell& cell) {
    m_cells.fill(cell);

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

void Maze::setPathStart(const Coords& position) {
    m_start = position;
}

void Maze::setPathDestination(const Coords& position) {
    m_end = position;
}

void Maze::setPathfinder(std::unique_ptr<IPathFinder> pathfinder) {
    m_pathfinder = std::move(pathfinder);
}

void Maze::findPath() {
    m_pathfinder->findPath(*this, m_start, m_end);
}

void Maze::registerObserver(IMazeObserver* observer) {
    m_observers.push_back(observer);
}