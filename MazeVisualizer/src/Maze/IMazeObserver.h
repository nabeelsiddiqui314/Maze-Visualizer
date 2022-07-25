#pragma once
#include "../Util/Coords.h"

class IMazeObserver {
public:
	IMazeObserver() = default;
	virtual ~IMazeObserver() = default;
public:
	virtual void onCellChange(const Coords& position) = 0;
};