#pragma once
#include "../Util/Coords.h"

enum class Cell;

class IMazeObserver {
public:
	IMazeObserver() = default;
	virtual ~IMazeObserver() = default;
public:
	virtual void onCellChange(const Coords& position) = 0;
	virtual void onCellSearch(const Coords& position) = 0;
	virtual void onFill(const Cell& cell) = 0;
};