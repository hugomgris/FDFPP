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
    : _rotationAngle(0.0), _MLXHandler(MLXHandler), _projector(projector), _heightMap(heightMap) {
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
    _OriginalRotationAngle = _rotationAngle;
    
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
    int drawX = x * _spacing;
    int drawY = y * _spacing;
    
    if (_rotationAngle != 0.0) {
        int centerX = _heightMap.getMatrixWidth() / 2 * _spacing;
        int centerY = _heightMap.getMatrixHeight() / 2 * _spacing;
        
        int tempX = drawX - centerX;
        int tempY = drawY - centerY;
        
        double cos_rot = cos(_rotationAngle);
        double sin_rot = sin(_rotationAngle);
        int rotatedX = tempX * cos_rot - tempY * sin_rot + centerX;
        int rotatedY = tempX * sin_rot + tempY * cos_rot + centerY;
        
        drawX = rotatedX;
        drawY = rotatedY;
    }
    
    std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, z);
    
    int centeredX = projectedPoint.first + _horizontalOffset;
    int centeredY = projectedPoint.second + _verticalOffset;
    
    int screenCenterX = _MLXHandler.getWidth() / 2;
    int screenCenterY = _MLXHandler.getHeight() / 2;
    
    int screenX = screenCenterX + ((centeredX - screenCenterX) - _cameraX) * _zoomLevel;
    int screenY = screenCenterY + ((centeredY - screenCenterY) - _cameraY) * _zoomLevel;
    
    return {screenX, screenY};
}

void Camera::rotate(double angle) {
    _rotationAngle += angle;
    while (_rotationAngle >= 2 * M_PI) _rotationAngle -= 2 * M_PI;
    while (_rotationAngle < 0) _rotationAngle += 2 * M_PI;
}

double Camera::getRotationAngle() const {
    return _rotationAngle;
}

void Camera::reset(){
    _zoomLevel = _OriginalZoomLevel;
    _cameraX = _OriginalCameraX;
    _cameraY = _OriginalCameraY;
    _horizontalOffset = _OriginalHorizontalOffset;
    _verticalOffset = _OriginalVerticalOffset;
    _spacing = _OriginalSpacing;
    _rotationAngle = _OriginalRotationAngle;
}