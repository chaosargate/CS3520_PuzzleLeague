#ifndef GRID_H
#define GRID_H

#include "Gem.h"
#include <stdlib.h>
namespace puzzle_league {

class Grid {
public:
    Grid();

    Gem* getGem(int x, int y) const noexcept;

    void swap(Gem **gem1, Gem **gem2) noexcept;

    bool getIsMoving() const noexcept;

    void setIsMoving(bool isMoving) noexcept;

    void findMatch() noexcept;

    void update() noexcept;

    void moveGems() noexcept;

    void deleteGems() noexcept;

private:
    // i is rows, j is columns
    Gem* grid_[13][7];
    int ts_ = 32;
    bool isMoving_ = false;
};
}

#endif
