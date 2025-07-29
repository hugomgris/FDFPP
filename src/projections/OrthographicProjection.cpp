/**
 * @file OrthographicProjection.cpp
 * @brief Implements the OrthographicProjection class for parallel projection.
 *
 * Orthographic projection eliminates perspective distortion by projecting 3D points
 * directly onto the 2D plane without depth scaling. This creates a flat, technical
 * drawing style where parallel lines remain parallel.
 */

#include "../../includes/projections//OrthographicProjection.hpp"

OrthographicProjection::~OrthographicProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using orthographic projection.
 * 
 * Simply ignores the Z-coordinate and returns the X and Y coordinates unchanged,
 * creating a flat, top-down view without any perspective effects.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (height) in 3D space (unused).
 * @return A pair containing the X and Y coordinates as 2D screen coordinates.
 */
std::pair<int, int> OrthographicProjection::project(int &x, int &y, int &z) const{
		(void)z;
		return {x, y};
}
