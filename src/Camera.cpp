/**
 * @file Camera.cpp
 * @brief Implements the Camera class, which manages zooming, panning, rotation,
 *        and coordinate transformation for rendering height maps.
 *
 * The Camera class is responsible for adjusting the view in 2D screen space
 * based on user interactions and applying geometrical transformations such as
 * zooming, panning, centering, and rotating the wireframe projection.
 */

#include "../includes/Camera.hpp"
#include <cmath>
#include <iostream>

/**
 * @brief Constructs a Camera object with references to rendering context and data.
 * 
 * Initializes camera transformation values and computes initial scale and offset
 * based on the height map and projection.
 * 
 * @param MLXHandler Reference to the MLX rendering context.
 * @param projector Pointer to the Projector used for coordinate projection.
 * @param heightMap Reference to the HeightMap being rendered.
 */
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

/**
 * @brief Destructor for the Camera class.
 */
Camera::~Camera() {}

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

/**
 * @brief Zooms the camera in or out by a given factor.
 * 
 * If a mouse position is provided, the zoom centers on that point to maintain
 * its screen position after scaling. Otherwise, it zooms toward the center.
 *
 * @param factor Zoom factor (values >1 zoom in, <1 zoom out).
 * @param mouseX X coordinate of the mouse on screen, or -1 if unused.
 * @param mouseY Y coordinate of the mouse on screen, or -1 if unused.
 */
void Camera::zoom(double factor, int mouseX, int mouseY) {
    if (mouseX >= 0 && mouseY >= 0) {
        double worldX = (mouseX - _MLXHandler.getWidth() / 2) / _zoomLevel + _cameraX;
        double worldY = (mouseY - _MLXHandler.getHeight() / 2) / _zoomLevel + _cameraY;

        _zoomLevel *= factor;

        _zoomLevel = std::max(0.1, std::min(_zoomLevel, 10.0));
        
        _cameraX = worldX - (mouseX - _MLXHandler.getWidth() / 2) / _zoomLevel;
        _cameraY = worldY - (mouseY - _MLXHandler.getHeight() / 2) / _zoomLevel;
    } else {
        _zoomLevel *= factor;
        _zoomLevel = std::max(0.1, std::min(_zoomLevel, 10.0));
    }
}

/**
 * @brief Moves the camera position by a given offset.
 * 
 * Pan movement is adjusted by the current zoom level for intuitive navigation.
 *
 * @param dx Horizontal movement in screen coordinates.
 * @param dy Vertical movement in screen coordinates.
 */
void Camera::pan(int dx, int dy) {
    _cameraX += dx / _zoomLevel;
    _cameraY += dy / _zoomLevel;
}

/**
 * @brief Centers the rendered map within the screen.
 *
 * Calculates the bounding box of the projected heightmap and computes the
 * necessary offsets to center it on screen, resetting the camera position
 * in the process.
 */
void Camera::centerCamera() {
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

    int mapCenterX = (minX + maxX) / 2;
    int mapCenterY = (minY + maxY) / 2;

    int screenCenterX = _MLXHandler.getWidth() / 2;
    int screenCenterY = _MLXHandler.getHeight() / 2;

    _horizontalOffset = screenCenterX - mapCenterX;
    _verticalOffset = screenCenterY - mapCenterY;
    
    _cameraX = 0;
    _cameraY = 0;
}

/**
 * @brief Calculates screen-space offsets to center the projected map.
 *
 * Projects each point in the heightmap to determine its bounds,
 * then sets horizontal and vertical offsets so that the entire map
 * appears centered in the window.
 */

void Camera::calculateOffset() {
    int minX = INT_MAX;
    int maxX = INT_MIN;
    int minY = INT_MAX;
    int maxY = INT_MIN;
    
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
    
    int projectedWidth = maxX - minX;
    int projectedHeight = maxY - minY;
    
    _horizontalOffset = ((_MLXHandler.getWidth() - projectedWidth) / 2) - minX;
    _verticalOffset = ((_MLXHandler.getHeight() - projectedHeight) / 2) - minY;
}

/**
 * @brief Computes initial spacing and adjusts Z-factor based on map dimensions.
 * 
 * Determines a base spacing value that ensures the map fits within the window,
 * and computes a suitable Z-scaling factor to maintain proportion with
 * horizontal dimensions, adapting to both wide and tall maps.
 */
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

/**
 * @brief Transforms world coordinates to screen-space using projection and camera state.
 * 
 * Applies spacing, rotation (X, Y, Z), and current zoom/pan values to convert
 * a 3D point in the heightmap into its final 2D screen position.
 *
 * @param x X coordinate in the height map grid.
 * @param y Y coordinate in the height map grid.
 * @param z Height value (Z-axis) at the given grid point.
 * @return A pair of integers representing the screen X and Y coordinates.
 */
std::pair<int, int> Camera::worldToScreen(int x, int y, int z) const {
    int drawX = x * _spacing;
    int drawY = y * _spacing;
    int drawZ = z;
    
    int centerX = _heightMap.getMatrixWidth() / 2 * _spacing;
    int centerY = _heightMap.getMatrixHeight() / 2 * _spacing;
    int centerZ = 0;

    drawX -= centerX;
    drawY -= centerY;
    drawZ -= centerZ;
    
    int originalX = drawX;
    int originalY = drawY;
    int originalZ = drawZ;

    if (_rotationAngleX != 0.0) {
        double cosX = cos(_rotationAngleX);
        double sinX = sin(_rotationAngleX);
        drawY = round(originalY * cosX - originalZ * sinX);
        drawZ = round(originalY * sinX + originalZ * cosX);
        
        originalY = drawY;
        originalZ = drawZ;
    }
    
    if (_rotationAngleY != 0.0) {
        double cosY = cos(_rotationAngleY);
        double sinY = sin(_rotationAngleY);
        drawX = round(originalX * cosY + originalZ * sinY);
        drawZ = round(-originalX * sinY + originalZ * cosY);
        
        originalX = drawX;
    }
    
    if (_rotationAngleZ != 0.0) {
        double cosZ = cos(_rotationAngleZ);
        double sinZ = sin(_rotationAngleZ);
        drawX = round(originalX * cosZ - originalY * sinZ);
        drawY = round(originalX * sinZ + originalY * cosZ);
    }

    drawX += centerX;
    drawY += centerY;
    drawZ += centerZ;

    std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, drawZ);
    
    int centeredX = projectedPoint.first + _horizontalOffset;
    int centeredY = projectedPoint.second + _verticalOffset;
    
    int screenCenterX = _MLXHandler.getWidth() / 2;
    int screenCenterY = _MLXHandler.getHeight() / 2;
    
    int screenX = screenCenterX + ((centeredX - screenCenterX) - _cameraX) * _zoomLevel;
    int screenY = screenCenterY + ((centeredY - screenCenterY) - _cameraY) * _zoomLevel;
    
    return {screenX, screenY};
}

/**
 * @name Rotation Methods
 * @brief Rotate the camera around the X, Y, or Z axes.
 * 
 * Each method adds the given angle to the respective rotation angle and ensures
 * the result stays within [0, 2π) for stability.
 * @{
 */
void rotateX(double angle);
void rotateY(double angle);
void rotateZ(double angle);
/** @} */
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

/**
 * @brief Resets the camera to its initial state.
 *
 * Restores original zoom, pan, spacing, and rotation values that were
 * set during initialization.
 */
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