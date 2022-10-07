#pragma once
#include "IMazeGenerator.h"
#include "../../Util/Coords.h"
#include "../../Util/Size.h"

class RecursiveDivision : public IMazeGenerator {
public:
	RecursiveDivision() = default;
	~RecursiveDivision() = default;
public:
	void generate(Maze& maze) override;
private:
	void divideArea(Maze& maze, const Coords& origin, const Size& size);
	int evenRandom(int lowerBound, int upperBound);
	int oddRandom(int lowerBound, int upperBound);
};