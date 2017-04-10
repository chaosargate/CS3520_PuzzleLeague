#ifndef GEM_H
#define GEM_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;

namespace puzzle_league {

/**
 * A gem can be green, pink, red, yellow or blue. It has a X and Y
 * coordinate indicating its sprite position and a row and column to indicate
 * its position on the grid which it belongs to. 3 or more gems can match
 * horizontally or vertically. When there is a match, the gems opacity is
 * gradually reduced to to 10, otherwise its initial value is 255.
 *
 *@author Fiona Hasanaj, Aaron Hoang
 */
class Gem {
public:

    /** Gem constructor **/
    Gem(/** X coordinate of the position of this gem. **/
        const int& x,
        /** Y coordinate of the position of this gem. **/
        const int& y,
        /** Row of the grid where this gem is located. **/
        const int& row,
        /** Column of the grid where this gem is located. **/
        const int& col,
        /** Type of this gem. **/
        const int& kind,
        /** Indicates whether this gem matches with other neighboring gems. **/
        const bool& match,
        /** Opacity of this gem. **/
        const int& alpha);

    /** Destructor **/
    ~Gem();

    /** Set X coordinate of this gem to the given x value. **/
    void setX(/** X value to set X coordinate of this gem to. **/
              const int& x) noexcept;

    /**
     * Get X coordinate of this gem.
     * @return X coordinate of this gem's position.
     */
    int getX() const noexcept;

    /** Set Y coordinate of this gem to the given y value. **/
    void setY(/** Y value to set Y coordinate of this gem to. **/
              const int& y) noexcept;

    /**
     * Get Y coordinate of this gem.
     * @return Y coordinate of this gem's position.
     */
    int getY() const noexcept;

    /** Set row of this gem to the given row value. **/
    void setRow(/** Row to set this gem's row to. **/
                const int& row) noexcept;

    /**
     * Get the row of the grid this gem belongs to.
     * @return Index of the row of the grid this gem belongs to.
     */
    int getRow() const noexcept;

    /** Set column of this gem to the given column value. **/
    void setCol(/** Column to set this gem's column to. **/
                const int& col) noexcept;

    /**
     * Get the column of the grid this gem belongs to.
     * @return Index of the column of the grid this gem belongs to.
     */
    int getCol() const noexcept;

    /** Set the kind of this gem. **/
    void setKind(/** Kind to assign to the gem. **/
                 const int& kind) noexcept;

    /**
     * Get the kind of this gem.
     * @return kind of this gem.
     */
    int getKind() const noexcept;

    /** Set whether this gem matches other neighboring gems. **/
    void setMatch(/** Match value to set to this gem. **/
                  const bool& match) noexcept;

    /**
     * Get whether this gem matches other neighboring gems.
     * @return Whether this gem is a match.
     */
    bool getMatch() const noexcept;

    /** Set opacity of this gem. **/
    void setAlpha(/** Opacity to be set to this gem. **/
                  const int& alpha) noexcept;

    /**
     * Get opacity of this gem.
     * @return opacity of this gem.
     */
    int getAlpha() const noexcept;

private:
    /** X coordinate of the position of this gem. **/
    int x_;
    /** Y coordinate of the position of this gem. **/
    int y_;
    /** Row of the grid this gem belongs to. **/
    int row_;
    /** Column of the grid this gem belongs to. **/
    int col_;
    /** Kind of the gem. (green, pink, red, yellow, blue) **/
    int kind_;
    /** Indicates whether this gem matches other neighboring gems in the grid. **/
    bool match_;
    /** Opacity of this gem. **/
    int alpha_;
};

}

#endif
