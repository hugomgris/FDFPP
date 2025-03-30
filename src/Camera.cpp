/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:42:29 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/20 17:15:59 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Camera.hpp"
#include <cmath>
#include <iostream>

Camera::Camera(MLXHandler &MLXHandler, Projector *projector, HeightMap &heightMap)
    : _rotationAngleX(0.0), _rotationAngleY(0.0), _rotationAngleZ(0.0), _MLXHandler(MLXHandler), _projector(projector), _heightMap(heightMap) {
    _zoomLevel = 1.0;
    _cameraX = 0;
    _cameraY = 0;
    _horizontalOffset = 0;
    _verticalOffset = 0;
    _spacing = 1.0;

    _OriginalZoomLevel = _zoomLevel;
    _OriginalCameraX = _cameraX;
    _OriginalCameraY = _cameraY;
    _OriginalHorizontalOffset = _horizontalOffset;
    _OriginalVerticalOffset = _verticalOffset;
    _OriginalSpacing = _spacing;
    _OriginalRotationAngleX = _rotationAngleX;
    _OriginalRotationAngleY = _rotationAngleY;
    _OriginalRotationAngleZ = _rotationAngleZ;
    
    calculateInitialScale();
    calculateOffset();
    centerCamera();
}

Camera::~Camera() {}

// Getters and Setters

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

// Methods
void Camera::zoom(double factor, int mouseX, int mouseY) {
    // If mouse position is provided, zoom toward that point
    if (mouseX >= 0 && mouseY >= 0) {
        // Calculate the world coordinates under the mouse before zooming
        double worldX = (mouseX - _MLXHandler.getWidth() / 2) / _zoomLevel + _cameraX;
        double worldY = (mouseY - _MLXHandler.getHeight() / 2) / _zoomLevel + _cameraY;
        
        // Apply zoom
        _zoomLevel *= factor;
        
        // Enforce min/max zoom levels
        _zoomLevel = std::max(0.1, std::min(_zoomLevel, 10.0));
        
        // Calculate new camera position to keep mouse over same world position
        _cameraX = worldX - (mouseX - _MLXHandler.getWidth() / 2) / _zoomLevel;
        _cameraY = worldY - (mouseY - _MLXHandler.getHeight() / 2) / _zoomLevel;
    } else {
        // Just zoom without adjusting camera position
        _zoomLevel *= factor;
        _zoomLevel = std::max(0.1, std::min(_zoomLevel, 10.0));
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
    double maxWindowDimension = std::min(_MLXHandler.getWidth(), _MLXHandler.getHeight()) * 0.8;
    double mapDimension = std::max(_heightMap.getMatrixWidth(), _heightMap.getMatrixHeight());
    
    _spacing = maxWindowDimension / mapDimension;
    
    int minZ = INT_MAX;
    int maxZ = INT_MIN;
    
    for (int y = 0; y < _heightMap.getMatrixHeight(); y++) {
        for (int x = 0; x < _heightMap.getMatrixWidth(); x++) {
            int z = _heightMap.getMatrix()[y][x];
            minZ = std::min(minZ, z);
            maxZ = std::max(maxZ, z);
        }
    }
    
    int zRange = maxZ - minZ;
    if (zRange > 0) {
        double mapSize = std::max(_heightMap.getMatrixWidth(), _heightMap.getMatrixHeight());
        
        double zToMapRatio = static_cast<double>(zRange) / mapSize;
        
        double baseFactor = 5.0;
        
        if (mapSize > 100) {
            baseFactor += log10(mapSize / 100.0) * 3.0;
        }
        
        double adaptiveFactor = 1.0;
        if (zToMapRatio > 1.0) {
            adaptiveFactor = 1.0 + log10(zToMapRatio) * 2.0;
        }
        
        double zFactor = (_spacing * mapSize) / (baseFactor * adaptiveFactor * zRange);
        
        if (mapSize > 500) {
            zFactor *= 1 + (0.5 * (500.0 / mapSize));
        }
        
        zFactor = std::max(0.1, std::min(zFactor, 10.0));
        
        _heightMap.setZFactor(zFactor - _heightMap.getZFactor(), 1);
    }
}

std::pair<int, int> Camera::worldToScreen(int x, int y, int z) const {
    // Scale coordinates based on spacing
    int drawX = x * _spacing;
    int drawY = y * _spacing;
    int drawZ = z;  // You might want to scale Z too based on your requirements
    
    // Calculate the center point of the heightmap for rotation
    int centerX = _heightMap.getMatrixWidth() / 2 * _spacing;
    int centerY = _heightMap.getMatrixHeight() / 2 * _spacing;
    int centerZ = 0;  // Adjust if needed
    
    // Translate to origin for rotation
    drawX -= centerX;
    drawY -= centerY;
    drawZ -= centerZ;
    
    // Store original values for rotation calculations
    int originalX = drawX;
    int originalY = drawY;
    int originalZ = drawZ;
    
    // Apply rotations using temporary variables to avoid precision loss
    // The trig functions return doubles, so we'll cast back to int at the end
    
    // Apply X-axis rotation (pitch)
    if (_rotationAngleX != 0.0) {
        double cosX = cos(_rotationAngleX);
        double sinX = sin(_rotationAngleX);
        drawY = round(originalY * cosX - originalZ * sinX);
        drawZ = round(originalY * sinX + originalZ * cosX);
        
        // Update for next rotation
        originalY = drawY;
        originalZ = drawZ;
    }
    
    // Apply Y-axis rotation (yaw)
    if (_rotationAngleY != 0.0) {
        double cosY = cos(_rotationAngleY);
        double sinY = sin(_rotationAngleY);
        drawX = round(originalX * cosY + originalZ * sinY);
        drawZ = round(-originalX * sinY + originalZ * cosY);
        
        // Update for next rotation
        originalX = drawX;
    }
    
    // Apply Z-axis rotation (roll)
    if (_rotationAngleZ != 0.0) {
        double cosZ = cos(_rotationAngleZ);
        double sinZ = sin(_rotationAngleZ);
        drawX = round(originalX * cosZ - originalY * sinZ);
        drawY = round(originalX * sinZ + originalY * cosZ);
    }
    
    // Translate back from origin
    drawX += centerX;
    drawY += centerY;
    drawZ += centerZ;
    
    // Project the 3D coordinates to 2D using the selected projection
    std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, drawZ);
    
    // Apply offset, camera position, and zoom
    int centeredX = projectedPoint.first + _horizontalOffset;
    int centeredY = projectedPoint.second + _verticalOffset;
    
    int screenCenterX = _MLXHandler.getWidth() / 2;
    int screenCenterY = _MLXHandler.getHeight() / 2;
    
    int screenX = screenCenterX + ((centeredX - screenCenterX) - _cameraX) * _zoomLevel;
    int screenY = screenCenterY + ((centeredY - screenCenterY) - _cameraY) * _zoomLevel;
    
    return {screenX, screenY};
}

void Camera::rotateX(double angle) {
    _rotationAngleX += angle;
    while (_rotationAngleX >= 2 * M_PI) _rotationAngleX -= 2 * M_PI;
    while (_rotationAngleX < 0) _rotationAngleX += 2 * M_PI;
}

void Camera::rotateY(double angle) {
    _rotationAngleY += angle;
    while (_rotationAngleY >= 2 * M_PI) _rotationAngleY -= 2 * M_PI;
    while (_rotationAngleY < 0) _rotationAngleY += 2 * M_PI;
}

void Camera::rotateZ(double angle) {
    _rotationAngleZ += angle;
    while (_rotationAngleZ >= 2 * M_PI) _rotationAngleZ -= 2 * M_PI;
    while (_rotationAngleZ < 0) _rotationAngleZ += 2 * M_PI;
}

double Camera::getRotationAngleX() const {
    return _rotationAngleX;
}

double Camera::getRotationAngleY() const {
    return _rotationAngleY;
}

double Camera::getRotationAngleZ() const {
    return _rotationAngleZ;
}

void Camera::reset(){
    _zoomLevel = _OriginalZoomLevel;
    _cameraX = _OriginalCameraX;
    _cameraY = _OriginalCameraY;
    _horizontalOffset = _OriginalHorizontalOffset;
    _verticalOffset = _OriginalVerticalOffset;
    _spacing = _OriginalSpacing;
    _rotationAngleX = _OriginalRotationAngleX;
    _rotationAngleY = _OriginalRotationAngleY;
    _rotationAngleZ = _OriginalRotationAngleZ;
}