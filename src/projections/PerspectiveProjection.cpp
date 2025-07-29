/**
 * @file PerspectiveProjection.cpp
 * @brief Implements the PerspectiveProjection class for realistic 3D perspective.
 *
 * Perspective projection simulates how the human eye sees objects, where distant
 * objects appear smaller. Uses a configurable viewing distance to control the
 * strength of the perspective effect.
 */

#include "../../includes/projections/PerspectiveProjection.hpp"

PerspectiveProjection::PerspectiveProjection(double distance) : _distance(distance) {}

PerspectiveProjection::~PerspectiveProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using perspective projection.
 * 
 * Applies perspective scaling based on the viewing distance and the object's depth.
 * Objects further from the viewer (negative Z) appear smaller, creating realistic
 * depth perception.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (depth) in 3D space.
 * @return A pair containing the perspective-corrected 2D screen coordinates.
 */
std::pair<int, int> PerspectiveProjection::project(int &x, int &y, int &z) const {
	double adjustedZ = -z;
	double scale = _distance / (_distance + adjustedZ);
	int newX = x * scale;
	int newY = y * scale;
	return {newX, newY};
}