#pragma once
#include <array>
#include "Coords.h"

namespace Directions {
	const Coords North = {  0, -1 };
	const Coords South = {  0,  1 };
	const Coords East  = {  1,  0 };
	const Coords West  = { -1,  0 };

	const std::array<Coords, 4> List = { North, South, East, West };
}