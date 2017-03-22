#ifndef GRID_H
#define GRID_H

#include "Gem.h"
#include <stdlib.h>
namespace puzzle_league {

class Gem;

class Grid {
public:
    Grid();

    void swap(int row, int col, Gem* g) noexcept;

    void findMatch() noexcept;

    void update() noexcept;

    void moveGems() noexcept;

private:
    // i is rows, j is columns
    Gem* grid_[12][6];
    int ts_ = 32;
    bool isMoving_ = false;
};
}

#endif
