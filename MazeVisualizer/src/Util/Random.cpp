#include "Random.h"

void Random::init() {
	srand(time(NULL));
}

int Random::get(int upperBound) {
	return rand() % upperBound;
}
