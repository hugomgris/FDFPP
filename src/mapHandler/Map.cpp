#include "../../includes/mapHandler/Map.hpp"
#include <stdexcept>

Map::Map() {}

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

bool Map::hasCustomColor(int x, int y) const {
    if (y < 0 || y >= getHeight() || x < 0 || x >= getWidth()) {
        return false;
    }
    return _mapData[y][x].hasCustomColor;
}
