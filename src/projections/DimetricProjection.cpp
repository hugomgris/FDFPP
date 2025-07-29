/**
 * @file DimetricProjection.cpp
 * @brief Implements the DimetricProjection class for dimetric axonometric projection.
 *
 * Dimetric projection is an axonometric projection where two of the three axes
 * are equally foreshortened. This creates a 3D view with specific angular
 * relationships that provide good visibility of multiple faces.
 */
 
#include "../../includes/projections/DimetricProjection.hpp"

DimetricProjection::~DimetricProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using dimetric projection.
 * 
 * Applies dimetric transformation using specific angles (π/8 and π/4) to create
 * the characteristic dimetric view where two axes have equal foreshortening.
 * The Z-coordinate directly affects the Y-position without angular transformation.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (height) in 3D space.
 * @return A pair containing the dimetric-projected 2D screen coordinates.
 */
std::pair<int, int> DimetricProjection::project(int &x, int &y, int &z) const {
    double alpha = M_PI / 8;
    double beta = M_PI / 4;
    int newX = x * cos(alpha) + y * cos(beta);
    int newY = x * sin(alpha) + y * sin(beta) - z;
    return {newX, newY};
}