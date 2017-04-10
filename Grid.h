#ifndef GRID_H
#define GRID_H

#include "Gem.h"
#include <stdlib.h>
namespace puzzle_league {

/**
 * The main play area of the game. The grid itself is populated with Gems
 * that can be swapped.
 *
 * @author Fiona Hasanaj, Aaron Hoang
 */
class Grid {
public:
    /** Grid constructor. **/
    Grid();

    /** Destructor. **/
    ~Grid();

    /**
     * Initialize a new row in this grid.
     * @throw out_of_range if i is outside the bounds of this grid.
     */
    void initRow(/** Index of the row to be initialized in this grid. **/
                 const int& i);

    /**
     * Get the gem that is located in the given row and column of this grid.
     * @return Gem located in the given row and column.
     * @throw out_of_range if the given row and column are outside the bounds
     *                     of this grid.
     */
    Gem* getGem(/** Column of the grid to retrieve the gem from. **/
                const int& col,
                /** Row of the grid to retrieve the gem from. **/
                const int& row) const;

    /**
     * Swap two gems in this grid.
     * @throw out_of_range if the coordinates of any of them gems are outside
     *                     the bounds of this grid.
     */
    void swap(/** First gem to be swapped. **/
              Gem **gem1,
              /** Second gem to be swapped. **/
              Gem **gem2);

    /**
     * Check if the gems in the grid are moving.
     * @return whether the gems in this grid are currently in motion.
     */
    bool getIsMoving() const noexcept;

    /** Set whether the gems in the grid are moving. **/
    void setIsMoving(/** Are the gems in this grid moving? */
                     const bool& isMoving) noexcept;

    /**
     * Scan the grid and find matches.
     */
    void findMatch() noexcept;

    /**
     * Scan the grid from the bottom up, and swap matches with non-matches,
     * so the matches will eventually be positioned at the top of the grid.
     */
    void update() noexcept;

    /**
     * Scan the grid and find the gems which have a difference between their
     * row, col and x, y values respectively and update the x and y values
     * of their position accordingly.
     */
    void moveGems() noexcept;

    /**
     * Gradually raise gems as the game progresses.
     */
    void raiseGems() noexcept;

    /**
     * Scan the grid and find all gems that are labeled as matches and
     * decrease their transparency by 1 if it is greater than 10.
     */
    void deleteGems() noexcept;

    /**
     * Get the score of the game.
     * @return score of the game.
     */
    int getScore() const noexcept;

    /**
     * Get the offset value, which represents the current number of pixels the
     * gems have moved upwards relative to the last row they should be in.
     * @return current offset.
     */
    int getOffset() const noexcept;

    /**
     * Update offset by the given value i.
     */
    void updateOffset(/** The value to increment offset_ by */
                      int i) noexcept;

    /**
     * Get the tile size of a gem in this grid.
     */
    int getTileSize() const noexcept;

private:
    /** Grid where i indicates rows, j indicates columns. **/
    Gem* grid_[14][7];
    /** Tile size of the gems in this grid. **/
    int ts_ = 32;
    /** Indicates whether the gems in this grid are moving. **/
    bool isMoving_ = false;
    /** Score of the game. **/
    int score_ = 0;
    /** Current number of pixels the gems have moved upwards vertically with. **/
    int offset_ = 0;
};
}

#endif
