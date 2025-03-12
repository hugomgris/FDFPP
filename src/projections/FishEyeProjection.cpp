/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FishEyeProjection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 14:29:01 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/FishEyeProjection.hpp"

FishEyeProjection::~FishEyeProjection(){}

std::pair<int, int> FishEyeProjection::project(int &x, int &y, int &z) const {
    double strength = 100.0;
    double r = sqrt(x*x + y*y);
    if (r < 0.001) return {x, y - z}; // Handle center point specially
    
    // Scale factor to make effect more visible
    double scale = 10.0;
    
    // Modified formula with better scaling
    double factor = scale * (1.0 / strength) * atan(r / (strength / scale));
    
    // Apply the distortion
    int newX = x * (factor / r);
    int newY = y * (factor / r) - z;
    
    return {newX, newY};
}