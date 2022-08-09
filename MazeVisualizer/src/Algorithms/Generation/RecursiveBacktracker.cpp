#include "RecursiveBacktracker.h"
#include "../../Maze/Maze.h"
#include <stack>
#include <vector>
#include "../../Util/Random.h"
#include "../../Util/Directions.h"

void RecursiveBacktracker::generate(Maze& maze) {
	maze.fill(Cell::WALL);

	std::stack<Coords> sectionStack;
	sectionStack.emplace(0, 0);

	while (!sectionStack.empty()) {
		Coords currentSection= sectionStack.top();
		Coords currentCell = currentSection * 2;

		maze.setCellAt(currentCell, Cell::EMPTY);

		std::vector<Coords> neighbors;

		for (auto& offset : Directions::List) {
			Coords neighborSection = currentSection + offset;
			if (doesSectionExist(maze, neighborSection) && !isSectionVisited(maze, neighborSection)) {
				neighbors.push_back(offset);
			}
		}

		if (!neighbors.empty()) {
			std::size_t neighborIndex = Random::get(neighbors.size());
			Coords neighborOffset = neighbors[neighborIndex];

			maze.setCellAt(currentCell + neighborOffset, Cell::EMPTY);
			sectionStack.push(currentSection + neighborOffset);
		}
		else
			sectionStack.pop();
	}
}

bool RecursiveBacktracker::doesSectionExist(const Maze& maze, const Coords& position) const {
	return !maze.isOutOfBounds(position * 2);
}

bool RecursiveBacktracker::isSectionVisited(const Maze& maze, const Coords& position) const {
	return maze.getCellAt(position * 2) == Cell::EMPTY;
}
