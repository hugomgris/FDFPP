/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeightMap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:42:05 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/04/02 15:04:42 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HeightMap.hpp"

HeightMap::HeightMap(std::vector<std::string> &map) : _zFactor(1.0) {
    _map.getMapData().clear();
    _minHeight = INT_MAX;
    _maxHeight = INT_MIN;
    
    for (const auto &line : map) {
        if (!line.empty()) {
            std::vector<Map::MapPoint> mapLine;
            parseMapLine(line, mapLine);
            _map.getMapData().push_back(mapLine);
        }
    }
    
    // Make sure all rows have the same width
    size_t maxWidth = 0;
    for (const auto &row : _map.getMapData()) {
        maxWidth = std::max(maxWidth, row.size());
    }
    
    for (auto &row : _map.getMapData()) {
        row.resize(maxWidth, Map::MapPoint(0));
    }
    
    // Calculate min and max height for normalization
    calculateMinMaxHeight();
    
    // For compatibility, populate the old matrix format
    _matrix.resize(_map.getMapData().size());
    for (size_t y = 0; y < _map.getMapData().size(); y++) {
        _matrix[y].resize(_map.getMapData()[y].size());
        for (size_t x = 0; x < _map.getMapData()[y].size(); x++) {
            _matrix[y][x] = _map.getMapData()[y][x].z;
        }
    }

    _zFactor = 1.0;
    _matrixHeight = _matrix.size();
    _matrixWidth = _matrix[0].size();

    _nPoints = getNPoints();
    _nEdges = getNEdges();
}

HeightMap::~HeightMap() {
}

void HeightMap::parseMapLine(const std::string &line, std::vector<Map::MapPoint> &points) {
    std::istringstream iss(line);
    std::string token;
    
    while (iss >> token) {
        int z = 0;
        int color = 0;
        bool hasCustomColor = false;
        
        // Check if token contains a comma (indicating color)
        size_t commaPos = token.find(',');
        if (commaPos != std::string::npos) {
            // Extract z-value
            std::string zStr = token.substr(0, commaPos);
            z = std::stoi(zStr);
            
            // Extract color value
            std::string colorStr = token.substr(commaPos + 1);
            if (colorStr.substr(0, 2) == "0x" || colorStr.substr(0, 2) == "0X") {
                // Parse hex color
                std::stringstream ss;
                ss << std::hex << colorStr.substr(2);
                ss >> color;
                hasCustomColor = true;
            }
        } else {
            // Just a z-value
            z = std::stoi(token);
        }
        
        // Add point to the line
        points.push_back(Map::MapPoint(z, color, hasCustomColor));
        
        // Update min and max height
        _minHeight = std::min(_minHeight, z);
        _maxHeight = std::max(_maxHeight, z);
    }
}

void HeightMap::calculateMinMaxHeight() {
    _minHeight = INT_MAX;
    _maxHeight = INT_MIN;

    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            int z = getZ(x, y);
            if (z < _minHeight)
                _minHeight = z;
            if (z > _maxHeight)
                _maxHeight = z;
        }
    }
}

int HeightMap::getMatrixWidth() const {
    return _map.getWidth();
}

int HeightMap::getMatrixHeight() const {
    return _map.getHeight();
}

int HeightMap::getZ(int x, int y) const {
    return _map.getZ(x, y) * _zFactor;
}

int HeightMap::getColor(int x, int y) const {
    return _map.getColor(x, y);
}

bool HeightMap::hasCustomColor(int x, int y) const {
    return _map.hasCustomColor(x, y);
}

float HeightMap::normalizeHeight(int z) const {
    if (_maxHeight == _minHeight) {
        return 0.5f;
    }
    return static_cast<float>(z - _minHeight) / (_maxHeight - _minHeight);
}

void HeightMap::setZFactor(double factor, int mode) {
    if (mode > 0)
        _zFactor += factor;
    if (mode < 0)
        _zFactor -= factor;
        
    // Recalculate height extremes after changing z factor
    calculateMinMaxHeight();
}

double HeightMap::getZFactor() const {
    return _zFactor;
}

int HeightMap::getNPoints() const {
    int totalPoints = 0;
    const std::vector<Map::MapLine>& mapData = _map.getMapData();

    for (const Map::MapLine &line : mapData){
        totalPoints += line.size();
    }

    std::cout << totalPoints << std::endl;
    return (totalPoints);
}

int HeightMap::getNEdges() const {
    int rows;
    int cols;
    int totalEdges;

    const std::vector<Map::MapLine>& mapData = _map.getMapData();
    rows = mapData.size();
    cols = mapData[0].size();

    totalEdges = (rows * (cols - 1) + (cols * (rows - 1)));
    return (totalEdges);
}