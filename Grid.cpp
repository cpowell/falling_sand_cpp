//
// Created by chris on 2/11/25.
//

#include "Grid.h"

Particle* Grid::getCell(const int row, const int col) {
    if (col < 0 || col >= width_) {
        return nullptr;
    }

    if (row < 0 || row >= height_) {
        return nullptr;
    }

    if (cells_[row][col] == nullptr) {
        return nullptr;
    }
    return cells_[row][col];
}

Grid::Kind Grid::cellType(const int row, const int col) const {
    if (col < 0 || col >= width_) {
        return Kind::Rock;
    }

    if (row < 0 || row >= height_) {
        return Kind::Rock;
    }

    if (cells_[row][col] == nullptr) {
        return Kind::None;
    } else if (cells_[row][col]->type_ == 's') {
        return Kind::Sand;
    } else if (cells_[row][col]->type_ == 'r') {
        return Kind::Rock;
    }
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
            if (cellType(row, col) == Kind::Sand) {
                Particle* pp = cells_[row][col];

                // Straight down if possible
                if (cellType(row + 1, col) == Kind::None) {
                    cells_[row + 1][col] = pp;
                    cells_[row][col] = nullptr;
                    continue;
                }

                // Otherwise look for a possible direction
                bool left_free = cellType(row + 1, col - 1) == Kind::None;
                bool right_free = cellType(row + 1, col + 1) == Kind::None;

                if (left_free && right_free) {
                    int new_row = row + 1;
                    int new_col = col;

                    if (dist(gen_)) {
                        --new_col;
                    } else {
                        ++new_col;
                    }
                    cells_[new_row][new_col] = pp;
                    cells_[row][col] = nullptr;
                } else if (left_free) {
                    int new_row = row + 1;
                    int new_col = col - 1;
                    cells_[new_row][new_col] = pp;
                    cells_[row][col] = nullptr;
                } else if (right_free) {
                    int new_row = row + 1;
                    int new_col = col + 1;
                    cells_[new_row][new_col] = pp;
                    cells_[row][col] = nullptr;
                }
            }
        }
    }
}
