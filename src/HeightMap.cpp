/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeightMap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:42:05 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/18 17:47:24 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HeightMap.hpp"
#include <iostream>

HeightMap::HeightMap(std::vector<std::string> &map) {
    for (const std::string & line : map){
        std::istringstream iss(line);
        std::vector<int> row;

        int value;
        while (iss >> value){
            row.push_back(value);
        }
        _matrix.push_back(row);
    }

    _zFactor = 1.0;
    _matrixHeight = _matrix.size();
    _matrixWidth = _matrix[0].size();
    calculateHeightExtremes();
}

HeightMap::~HeightMap() {}

std::vector<std::vector<int>> &HeightMap::getMatrix() {
    return _matrix;
}

int HeightMap::getMatrixWidth() const {
    return _matrixWidth;
}

int HeightMap::getMatrixHeight() const {
    return _matrixHeight;
}

double HeightMap::getZFactor() const {
    return _zFactor;
}

void HeightMap::setZFactor(double increase, int mode) {
    if (mode > 0)
        _zFactor += increase;
    if (mode < 0)
        _zFactor -= increase;
        
    // Recalculate height extremes after changing z factor
    calculateHeightExtremes();
}

int HeightMap::getZ(int x, int y) const {
    if (y < 0 || y >= _matrixHeight || x < 0 || x >= _matrixWidth)
        return (0);
    return (_matrix[y][x] * _zFactor);
}

void HeightMap::calculateHeightExtremes() {
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

float HeightMap::normalizeHeight(int z) const {
    // Ensure we don't divide by zero
    if (_maxHeight == _minHeight) {
        return 0.5f; // Return middle value if all heights are the same
    }
    
    // Normalize z to a value between 0.0 and 1.0
    return (static_cast<float>(z - _minHeight) / (_maxHeight - _minHeight));
}

void HeightMap::printMatrix() const {
    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            std::cout << getZ(x, y) << " ";
        }
        std::cout << std::endl;
    }
}