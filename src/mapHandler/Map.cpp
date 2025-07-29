/**
# * @file Map.cpp
# * @brief Implements the Map class for storing and accessing map grid data.
# *
# * The Map class manages a 2D grid of points, each with height (z), color, and custom color flag.
# * Provides methods for accessing map dimensions, Z values, colors, and custom color status.
# */

#include "../../includes/mapHandler/Map.hpp"
#include <stdexcept>

/**
 * @brief Constructs a Map object with an empty map data grid.
 */
Map::Map() {}

/**
 * @brief Destructor for Map. Cleans up map data if needed.
 */
Map::~Map() {}

int Map::getWidth() const {
    return _mapData.empty() ? 0 : _mapData[0].size();
}

int Map::getHeight() const {
    return _mapData.size();
}

int Map::getZ(int x, int y) const {
    if (y < 0 || y >= getHeight() || x < 0 || x >= getWidth()) {
        throw std::out_of_range("Coordinates out of map bounds");
    }
    return _mapData[y][x].z;
}

int Map::getColor(int x, int y) const {
    if (y < 0 || y >= getHeight() || x < 0 || x >= getWidth()) {
        throw std::out_of_range("Coordinates out of map bounds");
    }
    return _mapData[y][x].color;
}

/**
 * @brief Checks if the map point at (x, y) has a custom color defined.
 * @param x X coordinate (column).
 * @param y Y coordinate (row).
 * @return True if custom color is set, false otherwise.
 */
bool Map::hasCustomColor(int x, int y) const {
    if (y < 0 || y >= getHeight() || x < 0 || x >= getWidth()) {
        return false;
    }
    return _mapData[y][x].hasCustomColor;
}
