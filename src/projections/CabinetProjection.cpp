/**
 * @file CabinetProjection.cpp
 * @brief Implements the CabinetProjection class for oblique cabinet projection.
 *
 * Cabinet projection is a type of oblique projection where the front face appears
 * undistorted while receding edges are drawn at a 45-degree angle with half-length
 * scaling to reduce visual distortion.
 */

#include "../../includes/projections/CabinetProjection.hpp"

CabinetProjection::~CabinetProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using cabinet projection.
 * 
 * Applies cabinet projection with a 45-degree angle and 0.5 scaling factor
 * for the depth dimension. This creates a less distorted oblique view compared
 * to cavalier projection.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (depth) in 3D space.
 * @return A pair containing the cabinet-projected 2D screen coordinates.
 */
std::pair<int, int> CabinetProjection::project(int &x, int &y, int &z) const {
    double factor = 0.5;
    int newX = x + z * factor * cos(M_PI / 4);
    int newY = y - z * factor * sin(M_PI / 4);
    return {newX, newY};
}