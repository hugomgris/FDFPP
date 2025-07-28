/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConicProjection.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:00:00 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/07/28 15:22:47 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/ConicProjection.hpp"

ConicProjection::ConicProjection(double distance, double fugueX, double fugueY) 
    : _distance(distance), _fugueX(fugueX), _fugueY(fugueY) {}

ConicProjection::ConicProjection() : _distance(500.0), _fugueX(0.0), _fugueY(0.0) {}

ConicProjection::~ConicProjection(){}

std::pair<int, int> ConicProjection::project(int &x, int &y, int &z) const {
    // Elevated bird's-eye view conic projection
    // Start with isometric-like transformation, then apply perspective
    
    // First, apply an isometric-like rotation to get the elevated view
    double viewAngle = M_PI / 6; // 30 degrees - adjusts how "top-down" the view is
    
    // Rotate the coordinates to simulate looking down from above
    double rotatedX = x * cos(viewAngle) - y * sin(viewAngle);
    double rotatedY = x * sin(viewAngle) + y * cos(viewAngle);
    double rotatedZ = z;
    
    // Now apply perspective based on the rotated Y (which becomes our depth)
    double depth = rotatedY + _distance;
    if (depth <= 0.1) depth = 0.1; // Clamp to avoid extreme scaling
    
    double scale = _distance / depth;
    
    // Apply conic perspective transformation
    double projectedX = _fugueX + (rotatedX - _fugueX) * scale;
    // The rotated Y gives us the "receding into distance" effect
    // Z still controls height, but now with perspective scaling
    double projectedY = _fugueY + (rotatedZ * scale + rotatedY * 0.3); // Combine height and depth
    
    return {static_cast<int>(projectedX), static_cast<int>(projectedY)};
}