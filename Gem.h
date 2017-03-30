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
    Gem(int x, int y, int row, int col, int kind, bool match, int alpha);

    ~Gem();

    void setX(int x) noexcept;

    int getX() const noexcept;

    void setY(int y) noexcept;

    int getY() const noexcept;

    void setRow(int row) noexcept;

    int getRow() const noexcept;

    void setCol(int col) noexcept;

    int getCol() const noexcept;

    void setKind(int kind) noexcept;

    int getKind() const noexcept;

    void setMatch(bool match) noexcept;

    bool getMatch() const noexcept;

    void setAlpha(int alpha) noexcept;

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
