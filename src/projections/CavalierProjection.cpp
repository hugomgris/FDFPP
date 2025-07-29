/**
 * @file CavalierProjection.cpp
 * @brief Implements the CavalierProjection class for oblique cavalier projection.
 *
 * Cavalier projection is a type of oblique projection where receding lines are
 * drawn at a 45-degree angle with full-length scaling, maintaining the true
 * length of depth measurements.
 */

#include "../../includes/projections/CavalierProjection.hpp"

CavalierProjection::~CavalierProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using cavalier projection.
 * 
 * Applies cavalier projection with a 45-degree angle and full scaling (factor = 1.0)
 * for the depth dimension. This preserves the true length of receding edges but
 * may appear more distorted than cabinet projection.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (depth) in 3D space.
 * @return A pair containing the cavalier-projected 2D screen coordinates.
 */
std::pair<int, int> CavalierProjection::project(int &x, int &y, int &z) const {
    double angle = M_PI / 4;
    int newX = x + z * cos(angle);
    int newY = y - z * sin(angle);
    return {newX, newY};
}