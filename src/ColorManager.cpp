/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:43:10 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/04/03 14:27:17 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ColorManager.hpp"

ColorManager::ColorManager(HeightMap &heightMap) 
    : _heightMap(heightMap), _selectedColors(_colors1), _currentColorSet(0) {}

ColorManager::~ColorManager() {
}

int ColorManager::getColorFromHeight(int x, int y, int z) {
    // Check if this point has a custom color
    if (_heightMap.hasCustomColor(x, y)) {
        return _heightMap.getColor(x, y);
    }
    
    // If no custom color, use the height-based gradient
    float normalized = _heightMap.normalizeHeight(z);
    
    // Ensure the normalized value is between 0 and 1
    normalized = std::max(0.0f, std::min(1.0f, normalized));
    
    // Determine the index in the gradient - use COLOR_COUNT instead of sizeof
    int segment = static_cast<int>(normalized * (COLOR_COUNT - 1));
    
    // Get the two colors to interpolate between
    uint32_t colorA = _selectedColors[segment];
    uint32_t colorB = _selectedColors[std::min(segment + 1, COLOR_COUNT - 1)];
    
    // Interpolation factor between the two colors
    float localT = (normalized * (COLOR_COUNT - 1)) - segment;
    
    return interpolateColor(colorA, colorB, localT);
}

int ColorManager::interpolateColor(int color1, int color2, float t) {
    // Clamp t to [0.0, 1.0] range
    t = std::max(0.0f, std::min(1.0f, t));
    
    // Extract individual color channels
    int a1 = (color1 >> 24) & 0xFF;
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;
    
    int a2 = (color2 >> 24) & 0xFF;
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;
    
    // Linear interpolation between colors
    int a = static_cast<int>(a1 + t * (a2 - a1));
    int r = static_cast<int>(r1 + t * (r2 - r1));
    int g = static_cast<int>(g1 + t * (g2 - g1));
    int b = static_cast<int>(b1 + t * (b2 - b1));

    a = std::max(0, std::min(255, a));
    r = std::max(0, std::min(255, r));
    g = std::max(0, std::min(255, g));
    b = std::max(0, std::min(255, b));
    
    // Combine components into a single color
    return (a << 24) | (r << 16) | (g << 8) | b;
}