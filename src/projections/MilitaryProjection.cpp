/**
 * @file MilitaryProjection.cpp
 * @brief Implements the MilitaryProjection class for military-style projection.
 *
 * Military projection provides a simple orthographic-style view where the X-axis
 * remains unchanged and the Y-axis is offset by the height (Z) value, creating
 * a straightforward side-view representation.
 */
 
#include "../../includes/projections/MilitaryProjection.hpp"

MilitaryProjection::~MilitaryProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using military projection.
 * 
 * Applies a simple transformation where the X-coordinate remains unchanged
 * and the Y-coordinate is adjusted by subtracting the Z (height) value,
 * creating a side-view profile.
 * 
 * @param x X coordinate in 3D space (unchanged).
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (height) in 3D space.
 * @return A pair containing the military-projected 2D screen coordinates.
 */
std::pair<int, int> MilitaryProjection::project(int &x, int &y, int &z) const {
    int newX = x;
    int newY = y - z;
    return {newX, newY};
}