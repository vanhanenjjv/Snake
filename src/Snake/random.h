#ifndef RANDOM_H
#define RANDOM_H

/**
 * Random number generator.
 */
class Random {
public:
    Random();
    /**
     * Returns a random integer.
     * 
     * @param min Inclusive lower bound.
     * @param max Exclusive outer bound.
     * @return Random integer greater than or equal to `min` and less than `max`.
     */
    int Next(int min, int max);
};

#endif
