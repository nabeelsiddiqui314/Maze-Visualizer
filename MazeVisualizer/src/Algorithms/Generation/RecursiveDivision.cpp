#include "RecursiveDivision.h"
#include "../../Util/Random.h"
#include "../../Maze/Maze.h"

void RecursiveDivision::generate(Maze& maze) {
	maze.fill(Cell::EMPTY);
	divideArea(maze, {0, 0}, maze.getSize());
}

void RecursiveDivision::divideArea(Maze& maze, const Coords& origin, const Size& size) {
	if (size.width <= 2 && size.height <= 2) {
		return;
	}

	if (size.width > size.height) {
		int xDiv = evenRandom(origin.x + 1, origin.x + size.width - 1);

		for (int y = origin.y; y < origin.y + size.height; y++) {
			maze.setCellAt({ xDiv, y }, Cell::WALL);
		}

		int gapY = oddRandom(origin.y, origin.y + size.height);
		maze.setCellAt({ xDiv, gapY }, Cell::EMPTY);

		int xOffset = xDiv - origin.x;

		divideArea(maze, origin, { xOffset, size.height});
		divideArea(maze, { origin.x + xOffset + 1, origin.y }, { size.width - xOffset - 1, size.height });
	}
	else {
		int yDiv = evenRandom(origin.y + 1, origin.y + size.height - 1);
	
		for (int x = origin.x; x < origin.x + size.width; x++) {
			maze.setCellAt({ x, yDiv }, Cell::WALL);
		}
	
		int gapX = oddRandom(origin.x, origin.x + size.width);
		maze.setCellAt({ gapX, yDiv }, Cell::EMPTY);
	
		int yOffset = yDiv - origin.y;
	
		divideArea(maze, origin, { size.width, yOffset});
		divideArea(maze, { origin.x, origin.y + yOffset + 1 }, { size.width, size.height - yOffset - 1 });
	}
}

int RecursiveDivision::evenRandom(int lowerBound, int upperBound) {
	int number = Random::get(lowerBound, upperBound);

	if (number == lowerBound)
		return number;
	return number / 2 * 2;
}

int RecursiveDivision::oddRandom(int lowerBound, int upperBound) {
	int number = Random::get(lowerBound, upperBound);

	if (number == upperBound - 1)
		return number;
	return number / 2 * 2 + 1;
}
