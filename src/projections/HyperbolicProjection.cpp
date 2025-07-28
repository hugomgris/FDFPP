#include "../../includes/projections/HyperbolicProjection.hpp"

HyperbolicProjection::HyperbolicProjection() {}

HyperbolicProjection::~HyperbolicProjection(){}

std::pair<int, int> HyperbolicProjection::project(int &x, int &y, int &z) const {
    double scale = 1.0 / (1.0 + abs(z) * 0.05);
    int newX = x * scale;
    int newY = y * scale;
    return {newX, newY};
}