#ifndef GEM_H
#define GEM_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;

namespace puzzle_league {

class Gem {
public:

    Gem();

    Gem(const int& x, const int& y, const int& row, const int& col,
            const int& kind, const bool& match, const int& alpha);

    ~Gem();

    void setX(const int& x) noexcept;

    int getX() const noexcept;

    void setY(const int& y) noexcept;

    int getY() const noexcept;

    void setRow(const int& row) noexcept;

    int getRow() const noexcept;

    void setCol(const int& col) noexcept;

    int getCol() const noexcept;

    void setKind(const int& kind) noexcept;

    int getKind() const noexcept;

    void setMatch(const bool& match) noexcept;

    bool getMatch() const noexcept;

    void setAlpha(const int& alpha) noexcept;

    int getAlpha() const noexcept;

private:
    int x_;
    int y_;
    int row_;
    int col_;
    int kind_;
    bool match_;
    int alpha_;
};

}

#endif
