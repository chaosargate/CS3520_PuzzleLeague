#include "Gem.h"
using namespace puzzle_league;

Gem::Gem(const int& x, const int& y, const int& row, const int& col,
        const int& kind, const bool& match, const int& alpha) :
        x_(x), y_(y), row_(row), col_(col), kind_(kind), match_(match), alpha_(
                alpha) {}

Gem::~Gem() {}

void Gem::setX(const int& x) noexcept {
    x_ = x;
}

int Gem::getX() const noexcept {
    return x_;
}

void Gem::setY(const int& y) noexcept {
    y_ = y;
}

int Gem::getY() const noexcept {
    return y_;
}

void Gem::setRow(const int& row) noexcept {
    row_ = row;
}

int Gem::getRow() const noexcept {
    return row_;
}

void Gem::setCol(const int& col) noexcept {
    col_ = col;
}

int Gem::getCol() const noexcept {
    return col_;
}

void Gem::setKind(const int& kind) noexcept {
    kind_ = kind;
}

int Gem::getKind() const noexcept {
    return kind_;
}

void Gem::setMatch(const bool& match) noexcept
{
    match_ = match;
}

bool Gem::getMatch() const noexcept
{
    return match_;
}

void Gem::setAlpha(const int& alpha) noexcept {
    alpha_ = alpha;
}

int Gem::getAlpha() const noexcept {
    return alpha_;
}
