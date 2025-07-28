#include "../../includes/projections/IsometricProjection.hpp"

IsometricProjection::~IsometricProjection(){}

std::pair<int, int> IsometricProjection::project(int &x, int &y, int &z) const{
		int newX = (x - y) * std::cos(M_PI / 6);
		int newY = (x + y) * std::sin(M_PI / 6) - z;
		return {newX, newY};
}
