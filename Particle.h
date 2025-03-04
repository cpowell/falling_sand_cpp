#pragma once

class Grid;

#include <random>
#include <raylib.h>

class Particle {
public:
    enum class Kind {
        None,
        Sand,
        Rock
    };

    Particle(int row, int col, Kind kind);
    Particle& operator=(const Particle& other);
    Particle(const Particle& other);

    Kind kind_;
    Color color_;
    int row_;
    int col_;

protected:
    std::mt19937 gen_;
    std::random_device rd_;
    std::uniform_int_distribution<> dist_{ 0, 1 };
    std::uniform_int_distribution<> colordist_{ 0, 255 };
    std::uniform_real_distribution<double> rdist_{ 0.0, 1.0 };
};
