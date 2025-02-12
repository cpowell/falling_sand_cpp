#pragma once
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
        cells_.resize(height, std::vector<Kind>(width));
    }

    void setCell(const int row, const int col, Kind kind);

    Kind getCell(const int row, const int col) const;

    void evolve();

private:
    int height_, width_;

    std::vector<std::vector<Kind>> cells_;
    std::mt19937 gen_;
};
