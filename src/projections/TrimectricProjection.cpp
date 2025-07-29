/**
 * @file TrimetricProjection.cpp
 * @brief Implements the TrimetricProjection class for trimetric axonometric projection.
 *
 * Trimetric projection is an axonometric projection where all three axes have
 * different foreshortening ratios. This creates the most general form of
 * axonometric projection with maximum flexibility in viewing angles.
 */
 
#include "../../includes/projections/TrimetricProjection.hpp"

TrimetricProjection::~TrimetricProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using trimetric projection.
 * 
 * Applies trimetric transformation using three different angles (π/6, π/3, π/4)
 * for the X, Y, and Z axes respectively. This creates a unique 3D view where
 * each axis has its own distinct foreshortening ratio.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (height) in 3D space.
 * @return A pair containing the trimetric-projected 2D screen coordinates.
 */
std::pair<int, int> TrimetricProjection::project(int &x, int &y, int &z) const {
	double angleX = M_PI / 6;
    double angleY = M_PI / 3;
    double angleZ = M_PI / 4;
    
    int newX = x * cos(angleX) - y * cos(angleY);
    int newY = x * sin(angleX) + y * sin(angleY) - z * sin(angleZ);
    return {newX, newY};
}