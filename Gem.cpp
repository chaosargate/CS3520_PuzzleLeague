#include "Gem.h"
using namespace puzzle_league;

Gem::Gem(int x, int y, int row, int col, int kind, bool match, int alpha) {
    x_ = x;
    y_ = y;
    row_ = row;
    col_ = col;
    kind_ = kind;
    match_ = match;
    alpha_ = alpha;
}

Gem::~Gem() {
    cout << "Deleting gem!" << endl;
}

void Gem::setX(int x) noexcept {
    x_ = x;
}

int Gem::getX() const noexcept {
    return x_;
}

void Gem::setY(int y) noexcept {
    y_ = y;
}

int Gem::getY() const noexcept {
    return y_;
}

void Gem::setRow(int row) noexcept {
    row_ = row;
}

int Gem::getRow() const noexcept {
    return row_;
}

void Gem::setCol(int col) noexcept {
    col_ = col;
}

int Gem::getCol() const noexcept {
    return col_;
}

void Gem::setKind(int kind) noexcept {
    kind_ = kind;
}

int Gem::getKind() const noexcept {
    return kind_;
}

void Gem::setMatch(bool match) noexcept
{
    match_ = match;
}

bool Gem::getMatch() const noexcept
{
    return match_;
}

void Gem::setAlpha(int alpha) noexcept {
    alpha_ = alpha;
}

void Gem::swap(Gem* gem, Grid* grid) noexcept
{
    //std::swap(getCol(), gem->getCol());
    //std::swap(getRow(), gem->getRow());

    grid->swap(getRow(), getCol(), this);
    grid->swap(gem->getRow(), gem->getCol(), gem);
}
