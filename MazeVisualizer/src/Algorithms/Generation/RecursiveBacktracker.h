#pragma once
#include "IMazeGenerator.h"
#include "../../Util/Coords.h"

class RecursiveBacktracker : public IMazeGenerator {
public:
	RecursiveBacktracker() = default;
	~RecursiveBacktracker() = default;
public:
	void generate(Maze& maze) override;
private:
	bool doesSectionExist(const Maze& maze, const Coords& position) const;
	bool isSectionVisited(const Maze& maze, const Coords& position) const;
};