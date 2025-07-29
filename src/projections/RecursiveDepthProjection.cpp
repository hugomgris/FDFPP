/**
 * @file RecursiveDepthProjection.cpp
 * @brief Implements the RecursiveDepth class for recursive depth-based projection.
 *
 * Recursive depth projection creates a looping effect by wrapping the Z-coordinate
 * within a specified range and applying scaling based on the wrapped value. This
 * creates interesting visual patterns for deep or infinite-seeming structures.
 */

#include "../../includes/projections/RecursiveDepthProjection.hpp"

RecursiveDepth::~RecursiveDepth(){}

/**
 * @brief Projects 3D coordinates to 2D using recursive depth projection.
 * 
 * Wraps the Z-coordinate within a loop depth of 100 units and applies scaling
 * based on the wrapped value. This creates a recursive visual effect where
 * depth patterns repeat, useful for visualizing infinite or cyclic structures.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (height) in 3D space.
 * @return A pair containing the recursively-projected 2D screen coordinates.
 */
std::pair<int, int> RecursiveDepth::project(int &x, int &y, int &z) const {
    int loopDepth = 100;
    int wrappedZ = z % loopDepth;

    double scale = 1.0 / (1.0 + abs(wrappedZ) * 0.01);
    int newX = x * scale;
    int newY = y * scale;
    return {newX, newY};
}