#include "Particle.h"

#include "Grid.h"

Particle::Particle(int row, int col, Kind kind) : row_(row), col_(col), kind_(kind) {
    std::random_device rd;
    gen_.seed(rd());

    if (kind == Kind::Sand) {
        color_ = ColorFromHSV(rdist_(gen_) * 30, 0.3, 0.7);
    } else if (kind == Kind::Rock) {
        color_ = ColorFromHSV(rdist_(gen_) * 10, 0.1, 0.3);
    }
}

Particle& Particle::operator=(const Particle& other) {
    if (this == &other) {
        return *this;
    }
    kind_ = other.kind_;
    color_ = other.color_;
    row_ = other.row_;
    col_ = other.col_;
    return *this;
}

Particle::Particle(const Particle& other) {
    kind_ = other.kind_;
    color_ = other.color_;
    row_ = other.row_;
    col_ = other.col_;
}
