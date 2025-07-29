/**
 * @file HeightMap.cpp
 * @brief Implements the HeightMap class, which parses and stores 3D map data.
 *
 * The HeightMap handles parsing the string-based map input, storing Z-values
 * and optional per-point colors, and providing metrics and normalized height values.
 */

#include "../includes/HeightMap.hpp"

/**
 * @brief Constructs a HeightMap from a list of map strings.
 * 
 * Parses height and optional color information for each point, builds
 * the matrix of Z-values, and computes initial metrics such as dimensions
 * and height range.
 * 
 * @param map List of strings representing the map rows.
 */
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
    
    size_t maxWidth = 0;
    for (const auto &row : _map.getMapData()) {
        maxWidth = std::max(maxWidth, row.size());
    }
    
    for (auto &row : _map.getMapData()) {
        row.resize(maxWidth, Map::MapPoint(0));
    }
    
    calculateMinMaxHeight();
    
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

/**
 * @brief Destructor for HeightMap.
 */
HeightMap::~HeightMap() {}

/**
 * @brief Parses a line of the map into points with height and optional color.
 * 
 * Each token may be:
 * - just a Z value: `"5"`
 * - or a Z and color: `"10,0xFF0000"`
 *
 * Updates the min/max height while parsing.
 *
 * @param line String line from the map.
 * @param points Output vector to be filled with parsed points.
 */
void HeightMap::parseMapLine(const std::string &line, std::vector<Map::MapPoint> &points) {
    std::istringstream iss(line);
    std::string token;
    
    while (iss >> token) {
        int z = 0;
        int color = 0;
        bool hasCustomColor = false;
        
        size_t commaPos = token.find(',');
        if (commaPos != std::string::npos) {
            std::string zStr = token.substr(0, commaPos);
            z = std::stoi(zStr);
            
            std::string colorStr = token.substr(commaPos + 1);
            if (colorStr.substr(0, 2) == "0x" || colorStr.substr(0, 2) == "0X") {
                std::stringstream ss;
                ss << std::hex << colorStr.substr(2);
                ss >> color;
                hasCustomColor = true;
            }
        } else {
            z = std::stoi(token);
        }
        
        points.push_back(Map::MapPoint(z, color, hasCustomColor));
        
        _minHeight = std::min(_minHeight, z);
        _maxHeight = std::max(_maxHeight, z);
    }
}

/**
 * @brief Recalculates the minimum and maximum height values in the map.
 */
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

/**
 * @brief Returns the width of the matrix (number of columns).
 */
int HeightMap::getMatrixWidth() const {
    return _map.getWidth();
}

/**
 * @brief Returns the height of the matrix (number of rows).
 */
int HeightMap::getMatrixHeight() const {
    return _map.getHeight();
}

/**
 * @brief Gets the Z value at (x, y), applying Z scaling.
 */
int HeightMap::getZ(int x, int y) const {
    return _map.getZ(x, y) * _zFactor;
}

/**
 * @brief Gets the ARGB color value at (x, y), if available.
 */
int HeightMap::getColor(int x, int y) const {
    return _map.getColor(x, y);
}

/**
 * @brief Returns whether the point at (x, y) has a custom color.
 */
bool HeightMap::hasCustomColor(int x, int y) const {
    return _map.hasCustomColor(x, y);
}

/**
 * @brief Normalizes a Z value between 0.0 and 1.0 based on height range.
 */
float HeightMap::normalizeHeight(int z) const {
    if (_maxHeight == _minHeight) {
        return 0.5f;
    }
    return static_cast<float>(z - _minHeight) / (_maxHeight - _minHeight);
}

/**
 * @brief Sets the Z scaling factor.
 *
 * @param factor Amount to add or subtract.
 * @param mode Whether to increase (+1) or decrease (-1).
 */
void HeightMap::setZFactor(double factor, int mode) {
    if (mode > 0)
        _zFactor += factor;
    if (mode < 0)
        _zFactor -= factor;
        
    calculateMinMaxHeight();
}

/**
 * @brief Gets the current Z scaling factor.
 */
double HeightMap::getZFactor() const {
    return _zFactor;
}

/**
 * @brief Calculates the total number of map points.
 */
int HeightMap::getNPoints() const {
    int totalPoints = 0;
    const std::vector<Map::MapLine>& mapData = _map.getMapData();

    for (const Map::MapLine &line : mapData){
        totalPoints += line.size();
    }
    
    return (totalPoints);
}

/**
 * @brief Estimates the number of visual edges (connections between points).
 */
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