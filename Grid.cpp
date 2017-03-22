#include "Grid.h"
using namespace puzzle_league;

Grid::Grid() {
    // Initialize half of the grid.
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            grid_[i][j]->setKind(rand() % 5);
            grid_[i][j]->setCol(j);
            grid_[i][j]->setRow(i);
            grid_[i][j]->setX(j * ts_);
            grid_[i][j]->setY(i * ts_);
        }
    }
}

void Grid::swap(int row, int col, Gem* gem) noexcept {
    grid_[gem->getRow()][gem->getCol()] = gem;
}

void Grid::findMatch() noexcept {
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 5; j++) {
            if (grid_[i][j]) {
                // Find horizontal matches. Compare previous, current and next gem.
                if (grid_[i][j]->getKind() == grid_[i + 1][j]->getKind()) {
                    if (grid_[i][j]->getKind() == grid_[i - 1][j]->getKind()) {
                        for (int n = -1; n <= 1; n++)
                            grid_[i + n][j]->setMatch(true);
                    }
                }
                // Find vertical matches. Compare previous, current and next gem.
                if (grid_[i][j]->getKind() == grid_[i][j + 1]->getKind())
                    if (grid_[i][j]->getKind() == grid_[i][j - 1]->getKind())
                        for (int n = -1; n <= 1; n++)
                            grid_[i][j + n]->setMatch(true);
            }
        }
    }
}

void Grid::update() noexcept {
    //Update grid
    if (!isMoving_) {
        // Check for matches from the top row and moving downwards.
        for (int i = 11; i >= 0; i--)
            for (int j = 0; j < 6; j++)
                if (grid_[i][j]) {
                    if (grid_[i][j]->getMatch()) {
                        for (int n = i; n > 0; n--) {
                            if (!grid_[n][j]->getMatch()) {
                                grid_[n][j]->swap(grid_[i][j], this);
                                break;
                            };
                        }
                    }
                }

        for (int j = 0; j < 6; j++) {
            for (int i = 11, n = 0; i > 0; i--) {
                if (grid_[i][j]) {
                    if (grid_[i][j]->getMatch()) {
                        grid_[i][j]->setKind(rand() % 5);
                        grid_[i][j]->setX(-ts_ * n++);
                        grid_[i][j]->setMatch(false);
                        grid_[i][j]->setAlpha(255);
                    }
                }
            }
        }
    }
}

void Grid::moveGems() noexcept {
    for (int i = 1; i < 12; i++) {
        for (int j = 1; j < 6; j++) {
            if (grid_[i][j]) {
                Gem *gem = grid_[i][j];
                int dx, dy;
                for (int n = 0; n < 4; n++) {
                    dx = gem->getX() - gem->getCol() * ts_;
                    dy = gem->getY() - gem->getRow() * ts_;
                    if (dx) {
                        gem->setX(gem->getX() - dx / abs(dx));
                    }
                    if (dy) {
                        gem->setY(gem->getY() - dy / abs(dy));
                    }
                    if (dx || dy) {
                        //isMoving = 1
                    }
                }
            }
        }
    }
}

