/**
 * @file HyperbolicProjection.cpp
 * @brief Implements the HyperbolicProjection class for hyperbolic geometric projection.
 *
 * Hyperbolic projection creates a unique visual effect by applying non-linear
 * scaling based on the Z-coordinate, simulating hyperbolic geometry where
 * distance affects the scaling factor exponentially.
 */
 
#include "../../includes/projections/HyperbolicProjection.hpp"

HyperbolicProjection::HyperbolicProjection() {}

HyperbolicProjection::~HyperbolicProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using hyperbolic projection.
 * 
 * Applies a hyperbolic scaling factor based on the absolute Z-coordinate value.
 * Points with higher Z-values (further from the origin) are scaled down more
 * dramatically, creating a curved space effect similar to hyperbolic geometry.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (height) in 3D space.
 * @return A pair containing the hyperbolically-projected 2D screen coordinates.
 */
std::pair<int, int> HyperbolicProjection::project(int &x, int &y, int &z) const {
    double scale = 1.0 / (1.0 + abs(z) * 0.05);
    int newX = x * scale;
    int newY = y * scale;
    return {newX, newY};
}