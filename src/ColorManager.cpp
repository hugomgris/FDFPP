/**
 * @file ColorManager.cpp
 * @brief Implements the ColorManager class, which provides color interpolation
 *        for height-based rendering.
 *
 * Responsible for mapping height values in the heightmap to color gradients,
 * using either predefined or custom color sets. Supports smooth interpolation
 * between color segments and respects per-point overrides.
 */

#include "../includes/ColorManager.hpp"

/**
 * @brief Constructs a ColorManager for the given height map.
 * 
 * @param heightMap Reference to the HeightMap used for determining heights and custom colors.
 */
ColorManager::ColorManager(HeightMap &heightMap) 
    : _heightMap(heightMap), _selectedColors(_colors1), _currentColorSet(0) {}

/**
 * @brief Destructor for ColorManager.
 */
ColorManager::~ColorManager() {
}

/**
 * @brief Computes the final color for a heightmap point based on its height.
 * 
 * If the point has a custom color defined in the height map, that color is returned.
 * Otherwise, the height is normalized and used to interpolate between two neighboring
 * colors in the active palette.
 * 
 * @param x X coordinate in the height map.
 * @param y Y coordinate in the height map.
 * @param z Height value at the (x, y) position.
 * @return A 32-bit integer representing the final ARGB color.
 */
int ColorManager::getColorFromHeight(int x, int y, int z) {
    if (_heightMap.hasCustomColor(x, y)) {
        return _heightMap.getColor(x, y);
    }
    
    float normalized = _heightMap.normalizeHeight(z);
    
    normalized = std::max(0.0f, std::min(1.0f, normalized));
    
    int segment = static_cast<int>(normalized * (COLOR_COUNT - 1));
    
    uint32_t colorA = _selectedColors[segment];
    uint32_t colorB = _selectedColors[std::min(segment + 1, COLOR_COUNT - 1)];
    
    float localT = (normalized * (COLOR_COUNT - 1)) - segment;
    
    return interpolateColor(colorA, colorB, localT);
}

/**
 * @brief Linearly interpolates between two ARGB colors.
 * 
 * Each channel (A, R, G, B) is interpolated independently, and the final
 * color is clamped to the 0–255 range for each component.
 * 
 * @param color1 First color (as 0xAARRGGBB).
 * @param color2 Second color (as 0xAARRGGBB).
 * @param t Interpolation factor between 0.0 (color1) and 1.0 (color2).
 * @return Interpolated ARGB color as a 32-bit integer.
 */
int ColorManager::interpolateColor(int color1, int color2, float t) {
    t = std::max(0.0f, std::min(1.0f, t));
    
    int a1 = (color1 >> 24) & 0xFF;
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;
    
    int a2 = (color2 >> 24) & 0xFF;
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    int a = static_cast<int>(a1 + t * (a2 - a1));
    int r = static_cast<int>(r1 + t * (r2 - r1));
    int g = static_cast<int>(g1 + t * (g2 - g1));
    int b = static_cast<int>(b1 + t * (b2 - b1));

    a = std::max(0, std::min(255, a));
    r = std::max(0, std::min(255, r));
    g = std::max(0, std::min(255, g));
    b = std::max(0, std::min(255, b));

    return (a << 24) | (r << 16) | (g << 8) | b;
}