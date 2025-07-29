/**
 * @file SphericalConicProjection.cpp
 * @brief Implements the SphericalConicProjection class for spherical conic projection.
 *
 * Spherical conic projection first maps 3D coordinates onto a spherical surface,
 * then applies conic perspective projection. This creates unique curved perspective
 * effects useful for visualizing data on spherical or curved surfaces.
 */

#include "../../includes/projections/SphericalConicProjection.hpp"

SphericalConicProjection::SphericalConicProjection(double radius) : _radius(radius) {}
SphericalConicProjection::SphericalConicProjection() : _radius(400.0) {}
SphericalConicProjection::~SphericalConicProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using spherical conic projection.
 * 
 * First normalizes the 3D coordinates to lie on a sphere of the specified radius,
 * then applies a conic perspective transformation. The spherical mapping ensures
 * all points lie on the sphere surface before the final 2D projection.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (height) in 3D space.
 * @return A pair containing the spherical-conic-projected 2D screen coordinates.
 */
 
std::pair<int, int> SphericalConicProjection::project(int &x, int &y, int &z) const {
    double distance = sqrt(x*x + y*y + z*z);
    if (distance == 0) distance = 1;
    
    double sphereX = x * _radius / distance;
    double sphereY = y * _radius / distance;
    double sphereZ = z * _radius / distance;
    
    double depth = _radius + sphereY;
    if (depth <= 0.1) depth = 0.1;
    double scale = _radius / depth;
    
    int newX = sphereX * scale;
    int newY = sphereZ * scale;

    return {newX, newY};
}