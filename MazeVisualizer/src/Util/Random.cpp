#include "Random.h"

namespace {
	bool seeded = false;
}

void seed() {
	srand(time(NULL));
	seeded = true;
}

namespace Random {
	int get(int upperBound) {
		if (!seeded)
			seed();

		return rand() % upperBound;
	}

	int get(int lowerBound, int upperBound) {
		return get(upperBound - lowerBound) + lowerBound;
	}
}