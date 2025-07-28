#include "../../includes/projections/CavalierProjection.hpp"

CavalierProjection::~CavalierProjection(){}

std::pair<int, int> CavalierProjection::project(int &x, int &y, int &z) const {
    double angle = M_PI / 4;
    int newX = x + z * cos(angle);
    int newY = y - z * sin(angle);
    return {newX, newY};
}