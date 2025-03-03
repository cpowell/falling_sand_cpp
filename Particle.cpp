#include "Particle.h"

#include "Grid.h"

Particle::Particle(int row, int col, int type) : row_(row), col_(col), type_(type) {
    if (type == 's') {
        color_ = GOLD;
    } else if (type == 'r') {
        color_ = GRAY;
    }
}

Particle & Particle::operator=(const Particle &other) {
    if (this == &other) {
        return *this;
    }
    type_ = other.type_;
    color_ = other.color_;
    row_ = other.row_;
    col_ = other.col_;
    return *this;
}

Particle::Particle(const Particle &other) {
    type_ = other.type_;
    color_ = other.color_;
    row_ = other.row_;
    col_ = other.col_;
}

SandParticle::SandParticle(int row, int col) : Particle(row, col, 's') {
    gen_.seed(rd_());
}

void SandParticle::update(const Grid& grid) {
    // Straight down if possible
    if (grid.cellType(row_ + 1, col_) == Grid::Kind::None) {
        ++row_;
    }

    // Otherwise look for a possible direction
    bool left_free = grid.cellType(row_ + 1, col_ - 1) == Grid::Kind::None;
    bool right_free = grid.cellType(row_ + 1, col_ + 1) == Grid::Kind::None;

    if (left_free && right_free) {
        ++row_;

        if (dist_(gen_)) {
            --col_;
        } else {
            ++col_;
        }
    } else if (left_free) {
        ++row_;
        --col_;
    } else if (right_free) {
        ++row_;
        ++col_;
    }
}

RockParticle::RockParticle(int row, int col): Particle(row, col, 'r') {
    // nop
}