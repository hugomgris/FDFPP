/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:34:25 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/27 14:21:52 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mapHandler/Map.hpp"
#include <stdexcept>

// Constructor and Destructor
Map::Map() {}

Map::~Map() {}

// Getters
std::vector<Map::MapLine>& Map::getMapData() { 
    return _mapData; 
}

const std::vector<Map::MapLine>& Map::getMapData() const { 
    return _mapData; 
}

// Utility methods
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
