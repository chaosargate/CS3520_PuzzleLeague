#include "Grid.h"
using namespace puzzle_league;

Grid::Grid() {
    // Initialize half of the grid.
    for (int i = 12; i > 0; i--) {
        for (int j = 1; j < 7; j++) {
            Gem *gem = new Gem(j * ts_, i * ts_, i, j, rand() % 5, true, 1);
            grid_[i][j] = gem;
            if (i > 6) {
                grid_[i][j]->setKind(rand() % 5);
                grid_[i][j]->setCol(j);
                grid_[i][j]->setRow(i);
                grid_[i][j]->setMatch(false);
                grid_[i][j]->setX(j * ts_);
                grid_[i][j]->setY(i * ts_);
                grid_[i][j]->setAlpha(255);
            }
        }
    }
}

Gem* Grid::getGem(const int& x, const int& y) const noexcept {
    Gem *gem = grid_[x][y];
    return gem;
}

void Grid::swap(Gem **gem1, Gem **gem2) noexcept {
    int col1 = (*gem1)->getCol();
    int col2 = (*gem2)->getCol();
    (*gem1)->setCol(col2);
    (*gem2)->setCol(col1);

    int row1 = (*gem1)->getRow();
    int row2 = (*gem2)->getRow();
    (*gem1)->setRow(row2);
    (*gem2)->setRow(row1);

    //(*gem1)->setMatch(true);

    Gem *temp = *gem2;
    grid_[(*gem1)->getRow()][(*gem1)->getCol()] = *gem1;
    grid_[temp->getRow()][temp->getCol()] = temp;
}

bool Grid::getIsMoving() const noexcept {
    return isMoving_;
}

void Grid::setIsMoving(const bool& isMoving) noexcept {
    isMoving_ = isMoving;
}
/**
 * Scan the grid and find matches.
 */
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

/**
 * Scan the grid from the bottom up, and swap matches with non-matches,
 * so the matches will eventually be positioned at the top of the grid.
 */
void Grid::update() noexcept {
    //Update grid
    if (!isMoving_) {
        // Check for matches from the bottom row and moving upwards.
        for (int i = 12; i > 0; i--) {
            for (int j = 1; j < 7; j++) {
                if (grid_[i][j]) {
                    // If a match is found, then scan the col from this position
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

/**
 * Scan the grid and find the gems which have a difference between their
 * row, col and x, y values respectively and change the x and y values
 * of their position accordingly.
 */
void Grid::moveGems() noexcept {
    for (int i = 1; i < 13; i++) {
        for (int j = 1; j < 7; j++) {
            if (grid_[i][j]) {
                Gem *gem = grid_[i][j];
                int dx, dy;
                for (int n = 0; n < 4; n++) { // n is speed
                    dx = gem->getX() - gem->getCol() * ts_;
                    dy = gem->getY() - gem->getRow() * ts_;

                    // If gem has swapped its row, then set x position accordingly
                    if (dx) {
                        gem->setX(gem->getX() - dx / abs(dx));
                    }
                    // If gem has swapped its col, then set y position accordingly
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
    if (!isMoving_) {
        for (int i = 1; i < 13; i++) {
            for (int j = 1; j < 7; j++) {
                if (grid_[i][j]) {
                    Gem *gem = grid_[i][j];
                    if (speed_ % 50 == 0) { // n is speed

                        gem->setY(gem->getY() - 1);
                        setIsMoving(false);

                    }
                }
            }
        }
        speed_++;
    }
}

/**
 * Scan the grid and find all gems that are labeled as matches and
 * decrease their transparency by 1 if it is greater than 1.
 */
void Grid::deleteGems() noexcept {
    if (!isMoving_) {
        for (int i = 1; i < 13; i++) {
            for (int j = 1; j < 7; j++) {
                if (grid_[i][j]) {
                    if (grid_[i][j]->getMatch()) {
                        if (grid_[i][j]->getAlpha() > 10) {
                            int alpha = grid_[i][j]->getAlpha();
                            if (alpha == 255) {
                                score_++;
                                cout << score_ << endl;
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

