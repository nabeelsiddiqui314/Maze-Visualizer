#pragma once
#include "../../Util/Coords.h"

class Maze;

class IPathFinder {
public:
	IPathFinder() = default;
	virtual ~IPathFinder() = default;
public:
	virtual void findPath(Maze& maze, const Coords& start, const Coords& destination) = 0;
};