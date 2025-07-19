//
// Created by chris on 2/11/25.
//

#include "Grid.h"
#include "effolkronium/random.hpp"

using Random = effolkronium::random_static;

void Grid::addParticle(const int row, const int col, Particle::Kind kind) {
    assert(row >= 0 && row < height_);
    assert(col >= 0 && col < width_);

    cells_[row][col] = new Particle{ row, col, kind };
}

void Grid::removeParticle(const int row, const int col) {
    assert(row >= 0 && row < height_);
    assert(col >= 0 && col < width_);

    if (cells_[row][col] != nullptr) {
        delete (cells_[row][col]);
        cells_[row][col] = nullptr;
    }
}

Particle* Grid::getParticle(const int row, const int col) const {
    if (col < 0 || col >= width_) {
        return nullptr;
    }

    if (row < 0 || row >= height_) {
        return nullptr;
    }

    return cells_[row][col];
}

Particle::Kind Grid::particleType(const int row, const int col) const {
    if (col < 0 || col >= width_) {
        return Particle::Kind::Rock;
    }

    if (row < 0 || row >= height_) {
        return Particle::Kind::Rock;
    }

    if (cells_[row][col] == nullptr) {
        return Particle::Kind::None;
    } else if (cells_[row][col]->kind_ == Particle::Kind::Sand) {
        return Particle::Kind::Sand;
    } else if (cells_[row][col]->kind_ == Particle::Kind::Rock) {
        return Particle::Kind::Rock;
    }

    return Particle::Kind::None; // failsafe
}

void Grid::evolve() {
    // Algorithm:
    // - If cell below is empty, move there
    // - If cell below is occupied:
    //   - if both diagonally-below cells are occupied, do nothing
    //   - if both diag cells are free, randomly choose one and move to it
    //   - move to the only free diag cell
    for (int row = height_ - 2; row >= 0; --row) {
        for (int col = 0; col < width_; ++col) {
            if (particleType(row, col) == Particle::Kind::Sand) {
                // Ok it's sand, now we can move it

                Particle* pp = cells_[row][col];

                // Straight down if possible
                if (particleType(row + 1, col) == Particle::Kind::None) {
                    cells_[row + 1][col] = pp;
                    cells_[row][col] = nullptr;
                    continue;
                }

                // Otherwise look for a possible direction
                bool left_free = particleType(row + 1, col - 1) == Particle::Kind::None;
                bool right_free = particleType(row + 1, col + 1) == Particle::Kind::None;

                if (left_free && right_free) {
                    int new_row = row + 1;
                    int new_col = col;

                    if (Random::get<bool>()) {
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
