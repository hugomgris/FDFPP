#include "../../includes/projections/CabinetProjection.hpp"

CabinetProjection::~CabinetProjection(){}

std::pair<int, int> CabinetProjection::project(int &x, int &y, int &z) const {
    double factor = 0.5;
    int newX = x + z * factor * cos(M_PI / 4);
    int newY = y - z * factor * sin(M_PI / 4);
    return {newX, newY};
}