/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:42:29 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/18 17:47:15 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Camera.hpp"
#include <cmath>
#include <iostream>

Camera::Camera(MLXHandler &MLXHandler, Projector *projector, HeightMap &heightMap)
    : _MLXHandler(MLXHandler), _projector(projector), _heightMap(heightMap) {
    _zoomLevel = 1.0;
    _cameraX = 0;
    _cameraY = 0;
    _horizontalOffset = 0;
    _verticalOffset = 0;
    _spacing = 1.0;
    
    calculateInitialScale();
    calculateOffset();
    centerCamera();
}

Camera::~Camera() {}

void Camera::zoom(double factor, int mouseX, int mouseY) {
    double oldZoom = _zoomLevel;
    _zoomLevel *= factor;
    
    // Enforce min/max zoom levels to prevent issues
    _zoomLevel = std::max(0.1, std::min(_zoomLevel, 10.0));
    
    // If mouse position is provided, zoom toward that point
    if (mouseX >= 0 && mouseY >= 0) {
        // Calculate the offset from screen center
        int centerX = _MLXHandler.getWidth() / 2;
        int centerY = _MLXHandler.getHeight() / 2;
        
        // Adjust camera position based on mouse position and zoom change
        _cameraX += (mouseX - centerX) * (1.0 / oldZoom - 1.0 / _zoomLevel);
        _cameraY += (mouseY - centerY) * (1.0 / oldZoom - 1.0 / _zoomLevel);
    }
}

void Camera::pan(int dx, int dy) {
    _cameraX += dx / _zoomLevel;
    _cameraY += dy / _zoomLevel;
}

void Camera::centerCamera() {
    // Find the minimum and maximum projected coordinates
    int minX = INT_MAX, minY = INT_MAX;
    int maxX = INT_MIN, maxY = INT_MIN;
    
    for (int y = 0; y < _heightMap.getMatrixHeight(); y++) {
        for (int x = 0; x < _heightMap.getMatrixWidth(); x++) {
            int z = _heightMap.getZ(x, y);
            int drawX = x * _spacing;
            int drawY = y * _spacing;
            
            std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, z);
            
            minX = std::min(minX, projectedPoint.first);
            minY = std::min(minY, projectedPoint.second);
            maxX = std::max(maxX, projectedPoint.first);
            maxY = std::max(maxY, projectedPoint.second);
        }
    }
    
    // Calculate the center of the map's bounding box
    int mapCenterX = (minX + maxX) / 2;
    int mapCenterY = (minY + maxY) / 2;
    
    // Calculate the screen center
    int screenCenterX = _MLXHandler.getWidth() / 2;
    int screenCenterY = _MLXHandler.getHeight() / 2;
    
    // Calculate the required offset to center the map
    _horizontalOffset = screenCenterX - mapCenterX;
    _verticalOffset = screenCenterY - mapCenterY;
    
    // Reset camera position (we'll use offsets for centering)
    _cameraX = 0;
    _cameraY = 0;
}

void Camera::calculateOffset() {
    // First find the min and max coordinates after projection
    int minX = INT_MAX;
    int maxX = INT_MIN;
    int minY = INT_MAX;
    int maxY = INT_MIN;
    
    // Calculate the projected bounds of the entire map
    for (int y = 0; y < _heightMap.getMatrixHeight(); y++) {
        for (int x = 0; x < _heightMap.getMatrixWidth(); x++) {
            int z = _heightMap.getZ(x, y);
            int drawX = x * _spacing;
            int drawY = y * _spacing;
            
            std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, z);
            
            minX = std::min(minX, projectedPoint.first);
            maxX = std::max(maxX, projectedPoint.first);
            minY = std::min(minY, projectedPoint.second);
            maxY = std::max(maxY, projectedPoint.second);
        }
    }
    
    // Calculate width and height of the projected map
    int projectedWidth = maxX - minX;
    int projectedHeight = maxY - minY;
    
    // Calculate offsets to center the projected map
    _horizontalOffset = ((_MLXHandler.getWidth() - projectedWidth) / 2) - minX;
    _verticalOffset = ((_MLXHandler.getHeight() - projectedHeight) / 2) - minY;
}

void Camera::calculateInitialScale() {
    // Calculate the initial scale factor based on window size and map dimensions
    double maxWindowDimension = std::min(_MLXHandler.getWidth(), _MLXHandler.getHeight()) * 0.8; // Use 80% of window
    double mapDimension = std::max(_heightMap.getMatrixWidth(), _heightMap.getMatrixHeight());
    
    // Calculate initial spacing
    _spacing = maxWindowDimension / mapDimension;
    
    int minZ = INT_MAX;
    int maxZ = INT_MIN;
    
    for (int y = 0; y < _heightMap.getMatrixHeight(); y++) {
        for (int x = 0; x < _heightMap.getMatrixWidth(); x++) {
            int z = _heightMap.getMatrix()[y][x]; // Direct access to raw matrix values
            minZ = std::min(minZ, z);
            maxZ = std::max(maxZ, z);
        }
    }
    
    int zRange = maxZ - minZ;
    if (zRange > 0) {
        double mapSize = std::max(_heightMap.getMatrixWidth(), _heightMap.getMatrixHeight());
        
        double scaleFactor;
        if (mapSize > 200) {
            // For extremely large maps
            scaleFactor = 10.0 + (mapSize - 200) * 0.05;
        } else if (mapSize > 100) {
            // For large maps
            scaleFactor = 7.0 + (mapSize - 100) * 0.03;
        } else {
            // For smaller maps
            scaleFactor = 5.0;
        }
        
        double zFactor = (_spacing * mapSize) / (scaleFactor * zRange);
        
        // Apply a logarithmic dampening for very large z-ranges
        if (zRange > 50) {
            zFactor *= (1.0 + log10(50.0 / zRange));
        }
        
        zFactor = std::max(0.5, std::min(zFactor, 20.0));
        
        // We need to update the heightMap's zFactor
        // Ideally, this would be done via a proper setter
        // but for the initial setup we'll allow this tight coupling
        // In a full refactoring, you might want to revisit this design
        _heightMap.setZFactor(zFactor - _heightMap.getZFactor(), 1);
    }
}

std::pair<int, int> Camera::worldToScreen(int x, int y, int z) const {
    int drawX = x * _spacing;
    int drawY = y * _spacing;
    
    // Project the point
    std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, z);
    
    // Apply horizontal and vertical offsets first (for centering)
    int centeredX = projectedPoint.first + _horizontalOffset;
    int centeredY = projectedPoint.second + _verticalOffset;
    
    // Calculate screen center
    int screenCenterX = _MLXHandler.getWidth() / 2;
    int screenCenterY = _MLXHandler.getHeight() / 2;
    
    // Then apply camera position and zoom relative to screen center
    int screenX = screenCenterX + ((centeredX - screenCenterX) - _cameraX) * _zoomLevel;
    int screenY = screenCenterY + ((centeredY - screenCenterY) - _cameraY) * _zoomLevel;
    
    return {screenX, screenY};
}

double Camera::getZoomLevel() const {
    return _zoomLevel;
}

int Camera::getCameraX() const {
    return _cameraX;
}

int Camera::getCameraY() const {
    return _cameraY;
}

int Camera::getHorizontalOffset() const {
    return _horizontalOffset;
}

int Camera::getVerticalOffset() const {
    return _verticalOffset;
}

double Camera::getSpacing() const {
    return _spacing;
}