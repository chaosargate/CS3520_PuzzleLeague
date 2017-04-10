#include "Grid.h"
using namespace puzzle_league;

Grid::Grid() {
    // Initialize the grid with opacity set to 1 for all the gems.
    for (int i = 13; i > 0; i--) {
        for (int j = 1; j < 7; j++) {
            Gem *gem = new Gem(j * ts_, i * ts_, i, j, rand() % 5, true, 1);
            grid_[i][j] = gem;
        }
        // Initialize half of the grid, by setting the opacity of the gems to 255.
        if (i > 6) {
            initRow(i);
        }
    }
}

Grid::~Grid() {}

void Grid::initRow(const int& i) {
    try {
        for (int j = 1; j < 7; ++j) {
            grid_[i][j]->setKind(rand() % 5);
            grid_[i][j]->setCol(j);
            grid_[i][j]->setRow(i);
            grid_[i][j]->setMatch(false);
            grid_[i][j]->setX(j * ts_);
            grid_[i][j]->setY(i * ts_);
            grid_[i][j]->setAlpha(255);
        }
    } catch (const std::out_of_range& oor) {
        cerr << "Can't access a gem outside the bounds of the grid: "
                << oor.what() << endl;
    }
}

Gem* Grid::getGem(const int& col, const int& row) const {
    Gem *gem;
    try {
        gem = grid_[col][row];
    } catch (const std::out_of_range& oor) {
        cerr << "Can't access a gem outside the bounds of the grid: "
                << oor.what() << endl;
    }
    return gem;
}

void Grid::swap(Gem **gem1, Gem **gem2) {
    // If the gems are not empty.
    if (*gem1 && *gem2) {
        int col1 = (*gem1)->getCol();
        int col2 = (*gem2)->getCol();
        (*gem1)->setCol(col2);
        (*gem2)->setCol(col1);

        int row1 = (*gem1)->getRow();
        int row2 = (*gem2)->getRow();
        (*gem1)->setRow(row2);
        (*gem2)->setRow(row1);
    }

    // If the coordinates of both gems are within the bounds of the grid, then swap them.
    try {
        Gem *temp = *gem2;
        grid_[(*gem1)->getRow()][(*gem1)->getCol()] = *gem1;
        grid_[temp->getRow()][temp->getCol()] = temp;
    } catch (const std::out_of_range& oor) {
        cerr
                << "Can't swap two gems with coordinates outside the bounds of the grid:  "
                << oor.what() << '\n';
    }
}

bool Grid::getIsMoving() const noexcept {
    return isMoving_;
}

void Grid::setIsMoving(const bool& isMoving) noexcept {
    isMoving_ = isMoving;
}

void Grid::findMatch() noexcept {
    for (int i = 1; i < 13; i++) {
        for (int j = 1; j < 7; j++) {
            if (grid_[i][j]) {
                // Find vertical matches. Compare previous, current and next gem.
                if (i > 1 && i < 12) {
                    if (grid_[i][j]->getKind() == grid_[i + 1][j]->getKind()
                            && grid_[i][j]->getAlpha() > 10
                            && grid_[i + 1][j]->getAlpha() > 10) {
                        if (grid_[i][j]->getKind() == grid_[i - 1][j]->getKind()
                                && grid_[i - 1][j]->getAlpha() > 10) {
                            for (int n = -1; n <= 1; n++) {
                                grid_[i + n][j]->setMatch(true);
                            }
                        }
                    }
                }
                // Find horizontal matches. Compare previous, current and next gem.
                if (j > 1 && j < 6) {
                    if (grid_[i][j]->getKind() == grid_[i][j + 1]->getKind()
                            && grid_[i][j]->getAlpha() > 10
                            && grid_[i][j + 1]->getAlpha() > 10) {
                        if (grid_[i][j]->getKind() == grid_[i][j - 1]->getKind()
                                && grid_[i][j - 1]->getAlpha() > 10) {
                            for (int n = -1; n <= 1; n++) {
                                grid_[i][j + n]->setMatch(true);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Grid::update() noexcept {
    //Update grid
    if (!isMoving_) {
        // Check for matches from the bottom row and moving upwards.
        for (int i = 12; i > 0; i--) {
            for (int j = 1; j < 7; j++) {
                if (grid_[i][j]) {
                    // If a match is found, then scan the column from this position
                    // up and once a non-match is found, swap and break.
                    if (grid_[i][j]->getMatch()) {
                        for (int n = i - 1; n > 0; n--) {
                            if (!grid_[n][j]->getMatch()) {
                                swap(&(grid_[n][j]), &(grid_[i][j]));
                                break;
                            };
                        }
                    }
                }
            }
        }
    }
}

void Grid::moveGems() noexcept {
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j < 7; j++) {
            if (grid_[i][j]) {
                Gem *gem = grid_[i][j];
                int dx, dy;
                for (int n = 0; n < 4; n++) { // n is speed
                    dx = gem->getX() - gem->getCol() * ts_;

                    // We'll increment the position of Y by offset_ to gradually move the gems
                    // upwards so we can move the gems closer to the top.
                    dy = (gem->getY() - gem->getRow() * ts_) + offset_;

                    // If gem has changed its previous row, then set x position accordingly
                    if (dx) {
                        gem->setX(gem->getX() - dx / abs(dx));
                    }
                    // If gem has changed its previous col, then set y position accordingly
                    if (dy) {

                        gem->setY(gem->getY() - dy / abs(dy));
                    }
                    if (dx || dy) {
                        setIsMoving(true);
                    }
                }
            }
        }
    }
}

void Grid::raiseGems() noexcept {
    // If the gems in the grid are not moving, for each gem in the grid,
    // decrease their index of the row by 1.
    if (!isMoving_) {
        for (int i = 1; i < 13; ++i) {
            for (int j = 1; j < 7; ++j) {
                Gem *g1 = grid_[i][j];
                Gem *g2 = grid_[i + 1][j];
                swap(&g1, &g2);
            }
        }
        // Initialize the bottom row.
        initRow(13);

        // Given that, raiseGems() is called after the gems have gradually
        // increased their X coordinate by 32 pixels, we reset the offset_
        // after updating their row index accordingly.
        offset_ = 0;
    }
}

void Grid::deleteGems() noexcept {
    if (!isMoving_) {
        // Iterate over all gems of thid grid.
        for (int i = 1; i < 13; i++) {
            for (int j = 1; j < 7; j++) {
                if (grid_[i][j]) {
                    // If a match is found and the gem's opacity is greater
                    // than 10, then we decrease its alpha value by 10
                    if (grid_[i][j]->getMatch()) {
                        if (grid_[i][j]->getAlpha() > 10) {
                            int alpha = grid_[i][j]->getAlpha();
                            // In the meantime, keep track of the score as
                            // well, once a new match is first encountered.
                            if (alpha == 255) {
                                score_++;
                            }
                            grid_[i][j]->setAlpha(alpha - 10);
                            setIsMoving(true);
                        }
                    }
                }
            }
        }
    }
}

int Grid::getScore() const noexcept {
    return score_;
}

int Grid::getOffset() const noexcept {
    return offset_;
}

void Grid::updateOffset(int i) noexcept {
    offset_ += i;
}

int Grid::getTileSize() const noexcept {
    return ts_;
}
