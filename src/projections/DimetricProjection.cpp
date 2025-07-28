#include "../../includes/projections/DimetricProjection.hpp"

DimetricProjection::~DimetricProjection(){}

std::pair<int, int> DimetricProjection::project(int &x, int &y, int &z) const {
    double alpha = M_PI / 8;
    double beta = M_PI / 4;
    int newX = x * cos(alpha) + y * cos(beta);
    int newY = x * sin(alpha) + y * sin(beta) - z;
    return {newX, newY};
}