#pragma once

class Grid;

#include <random>
#include <raylib.h>

class Particle {
public:
    Particle(int row, int col, int type);
    Particle& operator=(const Particle& other);
    Particle(const Particle& other);
    virtual ~Particle() = default;

    virtual void update(const Grid& grid) = 0;

    char type_;
    Color color_;
    int row_;
    int col_;

protected:
    std::mt19937 gen_;
    std::random_device rd_;
    std::uniform_int_distribution<> dist_{ 0, 1 };
};


class SandParticle : public Particle {
public:
    SandParticle(int row, int col);

    void update(const Grid& grid) override;
};


class RockParticle : public Particle {
public:
    RockParticle(int row, int col);

    void update(const Grid& grid) override {
        // Do nothing
    }
};
