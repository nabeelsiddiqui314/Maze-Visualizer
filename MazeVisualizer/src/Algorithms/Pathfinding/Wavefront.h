#pragma once
#include "IPathfinder.h"

class Wavefront : public IPathFinder {
public:
	Wavefront() = default;
	~Wavefront() = default;
public:
	void findPath(Maze& maze, const Coords& start, const Coords& destination) override;
};