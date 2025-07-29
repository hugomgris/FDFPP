/**
 * @file IsometricProjection.cpp
 * @brief Implements the IsometricProjection class for isometric 3D to 2D projection.
 *
 * Isometric projection maintains equal scaling along all three axes and provides
 * a classic 3D visualization commonly used in technical drawings and game graphics.
 * The projection uses a 30-degree angle to create the characteristic diamond-shaped view.
 */

#include "../../includes/projections/IsometricProjection.hpp"

IsometricProjection::~IsometricProjection(){}

/**
 * @brief Projects 3D coordinates to 2D using isometric projection.
 * 
 * Applies the standard isometric transformation that rotates the coordinate system
 * to show three faces of a 3D object equally. Uses 30-degree angles (π/6 radians)
 * to achieve the characteristic isometric view.
 * 
 * @param x X coordinate in 3D space.
 * @param y Y coordinate in 3D space.
 * @param z Z coordinate (height) in 3D space.
 * @return A pair containing the projected 2D screen coordinates (x, y).
 */
std::pair<int, int> IsometricProjection::project(int &x, int &y, int &z) const{
		int newX = (x - y) * std::cos(M_PI / 6);
		int newY = (x + y) * std::sin(M_PI / 6) - z;
		return {newX, newY};
}
