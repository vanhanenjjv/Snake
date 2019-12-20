#include "random.h"

#include <time.h>

#include <iostream>

Random::Random() {
    srand(time(NULL));
}

int Random::Next(int min, int max) {
    if (min > max)
        throw "Minimum value cannot be higher than maximum value.";
    else if (min == max)
        return min;
    else
        // Bias towards the lower end if the range of `rand()` isn't divisible by `(max - min)`.
        return rand() % (max - min) + min;
}
