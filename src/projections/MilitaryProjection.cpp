#include "../../includes/projections/MilitaryProjection.hpp"

MilitaryProjection::~MilitaryProjection(){}

std::pair<int, int> MilitaryProjection::project(int &x, int &y, int &z) const {
    int newX = x;
    int newY = y - z;
    return {newX, newY};
}