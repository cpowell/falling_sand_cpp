//
// Created by chris on 2/11/25.
//

#include "Grid.h"

void Grid::setCell(const int row, const int col, Kind kind) {
    assert(col >= 0);
    assert(col < width_);
    assert(row >= 0);
    assert(row < height_);
    cells_[row][col] = kind;
}

Grid::Kind Grid::getCell(const int row, const int col) const {
    // assert(col >= 0);
    // assert(col < width_);
    // assert(row >= 0);
    // assert(row < height_);
    if (col < 0 || col >= width_) {
        return Kind::Rock;
    }

    if (row < 0 || row >= height_) {
        return Kind::Rock;
    }

    return cells_[row][col];
}

void Grid::evolve() {
    std::random_device rd;
    gen_.seed(rd());
    std::uniform_int_distribution<> dist(0, 1);

    // Algorithm:
    // - If cell below is empty, move there
    // - If cell below is occupied:
    //   - if both diagonally-below cells are occupied, do nothing
    //   - if both diag cells are free, randomly choose one and move to it
    //   - move to the only free diag cell
    for (int row = height_ - 2; row >= 0; --row) {
        for (int col = 0; col < width_; ++col) {
            if (getCell(row, col) == Kind::Sand) {
                if (getCell(row + 1, col) == Kind::None) {
                    cells_[row + 1][col] = Kind::Sand;
                    cells_[row][col] = Kind::None;
                    continue;
                }

                bool left_free = getCell(row + 1, col - 1) == Kind::None;
                bool right_free = getCell(row + 1, col + 1) == Kind::None;

                if (left_free && right_free) {
                    cells_[row][col] = Kind::None;

                    if (dist(gen_)) {
                        cells_[row + 1][col - 1] = Kind::Sand;
                    } else {
                        cells_[row + 1][col + 1] = Kind::Sand;
                    }
                } else if (left_free) {
                    cells_[row + 1][col - 1] = Kind::Sand;
                    cells_[row][col] = Kind::None;
                } else if (right_free) {
                    cells_[row + 1][col + 1] = Kind::Sand;
                    cells_[row][col] = Kind::None;
                }
            }
        }
    }
}
