#pragma once
#include "Particle.h"

#include <assert.h>
#include <random>
#include <vector>

class Grid {
public:
    enum class Kind {
        None,
        Sand,
        Rock
    };

    Grid(int width, int height) : height_(height), width_(width) {
        cells_.resize(height, std::vector<Particle*>(width));
    }

    void setCell(const int row, const int col, Particle* p) {
        assert(row >= 0 && row < height_);
        assert(col >= 0 && col < width_);
        cells_[row][col] = std::move(p);
    }

    Kind cellType(const int row, const int col) const;

    void evolve();

private:
    int height_, width_;

    std::vector<std::vector<Particle*>> cells_;

    std::mt19937 gen_;
};
