#include "Wavefront.h"
#include <queue>
#include "../../Util/Array2D.h"
#include "../../Maze/Maze.h"
#include "../../Util/Directions.h"

void Wavefront::findPath(Maze& maze, const Coords& start, const Coords& destination) {
	Array2D<int> distanceField(maze.getSize(), 0);
	std::queue<Coords> cellBfsQueue;

	distanceField[start] = 1;
	cellBfsQueue.push(start);

	while (!cellBfsQueue.empty()) {
		Coords cellPosition = cellBfsQueue.front();
		cellBfsQueue.pop();

		if (cellPosition == destination)
			break;

		for (auto& direction : Directions::List) {
			Coords neighborPosition = cellPosition + direction;

			if (maze.isOutOfBounds(neighborPosition))
				continue;

			Cell neighbor = maze.getCellAt(neighborPosition);
			int distance = distanceField[cellPosition];

			if (neighbor != Cell::WALL && distanceField[neighborPosition] == 0) {
				distanceField[neighborPosition] = distance + 1;
				cellBfsQueue.push(neighborPosition);
			}
		}
	}

	Coords currentPosition = destination;

	while (currentPosition != start) {
		maze.setCellAt(currentPosition, Cell::PATH);

		Coords centralPosition = currentPosition;
		int distance = distanceField[centralPosition];
	
		for (auto& direction : Directions::List) {
			Coords neighborPosition = centralPosition + direction;
			
			if (maze.isOutOfBounds(neighborPosition))
				continue;
	
			int neighborDistance = distanceField[neighborPosition];
	
			if (neighborDistance != 0 && neighborDistance < distance) {
				distance = neighborDistance;
				currentPosition = neighborPosition;
			}
		}
	}
}