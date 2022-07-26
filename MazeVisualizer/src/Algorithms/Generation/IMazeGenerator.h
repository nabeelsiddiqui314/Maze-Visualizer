#pragma once

class Maze;

class IMazeGenerator {
public:
	IMazeGenerator() = default;
	virtual ~IMazeGenerator() = default;
public:
	virtual void generate(Maze& maze) = 0;
};