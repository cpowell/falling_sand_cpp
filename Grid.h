#pragma once
#include "Particle.h"

#include <assert.h>
#include <random>
#include <vector>

class Grid {
public:
    Grid(int width, int height) : height_(height), width_(width) {
        cells_.resize(height, std::vector<Particle*>(width));
    }

    void addParticle(const int row, const int col, Particle::Kind kind);

    void removeParticle(const int row, const int col);

    Particle* getParticle(const int row, const int col) const;

    Particle::Kind particleType(const int row, const int col) const;

    void evolve();

private:
    int height_, width_;

    std::vector<std::vector<Particle*>> cells_;

    std::mt19937 gen_;
};
