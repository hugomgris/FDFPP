#include "../../includes/projections/RecursiveDepthProjection.hpp"

RecursiveDepth::~RecursiveDepth(){}

std::pair<int, int> RecursiveDepth::project(int &x, int &y, int &z) const {
    int loopDepth = 100;
    int wrappedZ = z % loopDepth;

    double scale = 1.0 / (1.0 + abs(wrappedZ) * 0.01);
    int newX = x * scale;
    int newY = y * scale;
    return {newX, newY};
}