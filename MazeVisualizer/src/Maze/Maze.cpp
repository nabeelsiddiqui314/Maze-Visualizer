#include "Maze.h"
#include "IMazeObserver.h"
#include "../Algorithms/Generation/IMazeGenerator.h"
#include "../Util/Random.h"

Maze::Maze(const Size& size) 
    : m_cells(size, Cell::EMPTY), 
      m_size(size),
      m_state(State::IDLE) {
    randomizePathEnds();
}

void Maze::setCellAt(const Coords& position, const Cell& cell) {
    m_cells[position] = cell;

    for (auto& observerPtr : m_observers) {
        if (auto observer = observerPtr.lock())
            observer->onCellChange(position);
    }
}

Cell Maze::getCellAt(const Coords& position) const {
    for (auto& observerPtr : m_observers) {
        if (auto observer = observerPtr.lock())
            observer->onCellSearch(position);
    }

    return m_cells[position];
}

void Maze::fill(const Cell& cell) {
    m_cells.fill(cell);

    for (auto& observerPtr : m_observers) {
        if (auto observer = observerPtr.lock())
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
    m_state = State::GENERATING;

    if (m_generator) {
        m_generator->generate(*this);
    }

    m_state = State::IDLE;
}

void Maze::setPathStart(const Coords& position) {
    m_start = position;
}

void Maze::setPathDestination(const Coords& position) {
    m_end = position;
}

void Maze::randomizePathEnds() {
    m_start = { Random::get(m_size.width), Random::get(m_size.height) };
    m_end = { Random::get(m_size.width), Random::get(m_size.height) };
}

Coords Maze::getPathStart() const {
    return m_start;
}

Coords Maze::getPathDestination() const {
    return m_end;
}

Maze::State Maze::getState() const {
    return m_state;
}

void Maze::setPathfinder(std::unique_ptr<IPathFinder> pathfinder) {
    m_pathfinder = std::move(pathfinder);
}

void Maze::findPath() {
    m_state = State::PATHFINDING;

    if (m_pathfinder) {
        m_pathfinder->findPath(*this, m_start, m_end);
    }

    m_state = State::IDLE;
}

void Maze::registerObserver(const ObserverPtr& observer) {
    m_observers.push_back(observer);
}