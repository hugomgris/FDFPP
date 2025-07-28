#include "../../includes/projections/PerspectiveProjection.hpp"

PerspectiveProjection::PerspectiveProjection(double distance) : _distance(distance) {}

PerspectiveProjection::~PerspectiveProjection(){}

std::pair<int, int> PerspectiveProjection::project(int &x, int &y, int &z) const {
	double adjustedZ = -z;
	double scale = _distance / (_distance + adjustedZ);
	int newX = x * scale;
	int newY = y * scale;
	return {newX, newY};
}