/**
 * @file ConicProjection.cpp
 * @brief Implements the ConicProjection class for conic perspective projection.
 *
 * Conic projection combines perspective effects with rotational transformations
 * to create a complex 3D visualization. It includes configurable viewing distance
 * and vanishing point coordinates for advanced perspective control.
 */

#include "../../includes/projections/ConicProjection.hpp"

ConicProjection::ConicProjection(double distance, double fugueX, double fugueY) 
    : _distance(distance), _fugueX(fugueX), _fugueY(fugueY) {}

ConicProjection::ConicProjection() : _distance(500.0), _fugueX(0.0), _fugueY(0.0) {}

ConicProjection::~ConicProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using conic projection.
 * 
 * Applies a complex transformation involving rotation, perspective scaling,
 * and vanishing point calculations. First rotates the coordinates by 30 degrees
 * (π/6), then applies perspective division based on depth, and finally projects
 * toward the configured vanishing point.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (height) in 3D space.
 * @return A pair containing the conic-projected 2D screen coordinates.
 */
std::pair<int, int> ConicProjection::project(int &x, int &y, int &z) const {
    double viewAngle = M_PI / 6;
    
    double rotatedX = x * cos(viewAngle) - y * sin(viewAngle);
    double rotatedY = x * sin(viewAngle) + y * cos(viewAngle);
    double rotatedZ = z;
    
    double depth = rotatedY + _distance;
    if (depth <= 0.1) depth = 0.1;
    
    double scale = _distance / depth;
    
    double projectedX = _fugueX + (rotatedX - _fugueX) * scale;
    double projectedY = _fugueY + (rotatedZ * scale + rotatedY * 0.3);
    
    return {static_cast<int>(projectedX), static_cast<int>(projectedY)};
}