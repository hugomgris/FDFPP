/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:06:16 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/14 18:35:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.hpp"

//Constructor and destructor
FDF::FDF(std::vector<std::string> &map, Projector *projector, MLXHandler &MLXHandler, VFX *vfx): 
	_projector(projector), _MLXHandler(MLXHandler), _vfx(vfx){
		for (const std::string & line : map){
			std::istringstream iss(line);
			std::vector<int> row;

			int value;
			while (iss >> value){
				row.push_back(value);
			}
			_matrix.push_back(row);
		}

        _zoomLevel = 1.0;
        _cameraX = 0;
        _cameraY = 0;

		_matrixHeight = _matrix.size();
		_matrixWidth = _matrix[0].size();
		calculateInitialScale();
        calculateHeightExtremes();
        centerCamera();
}

FDF::~FDF(){}

//Getters and setters
std::vector<std::vector<int>> &FDF::getMatrix(){
	return (_matrix);
}

Projector *FDF::getProjector(){
    return (_projector);
}

VFX *FDF::getVFX(){
    return (_vfx);
}

double FDF::getZFactor(){
    return _zFactor;
}

void FDF::setZFactor(double increase, int mode){
    if (mode > 0)
        _zFactor += increase;
    if (mode < 0)
        _zFactor -= increase;
}

//Methods
int FDF::getZ(int x, int y) const{
    if (y < 0 || y >= _matrixHeight || x < 0 || x >= _matrixWidth)
        return (0);
    return (_matrix[y][x] * _zFactor);
}

void FDF::calculateOffset() {
    // First find the min and max coordinates after projection
    int minX = INT_MAX;
    int maxX = INT_MIN;
    int minY = INT_MAX;
    int maxY = INT_MIN;
    
    // Calculate the projected bounds of the entire map
    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            int z = getZ(x, y);
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

void FDF::calculateInitialScale(){
    // Calculate the initial scale factor based on window size and map dimensions
    double maxWindowDimension = std::min(_MLXHandler.getWidth(), _MLXHandler.getHeight()) * 0.8; // Use 80% of window
    double mapDimension = std::max(_matrixWidth, _matrixHeight);
    
    // Calculate initial spacing
    _spacing = maxWindowDimension / mapDimension;
    
    int minZ = INT_MAX;
    int maxZ = INT_MIN;
    
    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            int z = _matrix[y][x];
            minZ = std::min(minZ, z);
            maxZ = std::max(maxZ, z);
        }
    }
    
    int zRange = maxZ - minZ;
    if (zRange > 0) {
        double mapSize = std::max(_matrixWidth, _matrixHeight);
        
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
        
        _zFactor = (_spacing * mapSize) / (scaleFactor * zRange);
        
        // Apply a logarithmic dampening for very large z-ranges
        if (zRange > 50) {
            _zFactor *= (1.0 + log10(50.0 / zRange));
        }
        
        _zFactor = std::max(0.5, std::min(_zFactor, 20.0));
    }
}

void FDF::draw() {
	drawPoints();
	drawLines();
	mlx_image_to_window(_MLXHandler.getMLX(), _MLXHandler.getImage(), 0, 0);
}

void FDF::drawPoints() {
    int pointSize = 2;
    int screenCenterX = _MLXHandler.getWidth() / 2;
    int screenCenterY = _MLXHandler.getHeight() / 2;
    
    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            int z = getZ(x, y);
            int drawX = x * _spacing;
            int drawY = y * _spacing;
            
            // Project the point
            std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, z);
            
            // Apply horizontal and vertical offsets first (for centering)
            int centeredX = projectedPoint.first + _horizontalOffset;
            int centeredY = projectedPoint.second + _verticalOffset;
            
            // Then apply camera position and zoom relative to screen center
            int screenX = screenCenterX + ((centeredX - screenCenterX) - _cameraX) * _zoomLevel;
            int screenY = screenCenterY + ((centeredY - screenCenterY) - _cameraY) * _zoomLevel;
            
            // Apply jittering effect
            std::pair<int, int> screenPoint = {screenX, screenY};
            auto jitteredPoint = _vfx->jitter(screenPoint);
            
            int finalX = jitteredPoint.first;
            int finalY = jitteredPoint.second;
            
            // Draw point only if it's within bounds
            for (int i = -pointSize / 2; i <= pointSize / 2; i++) {
                for (int j = -pointSize / 2; j <= pointSize / 2; j++) {
                    int pixelX = finalX + i;
                    int pixelY = finalY + j;
                    
                    if (pixelX >= 0 && pixelX < _MLXHandler.getWidth() && 
                        pixelY >= 0 && pixelY < _MLXHandler.getHeight()) {
                        // Use the z value we already have
                        int color = getColorFromHeight(z);
                        mlx_put_pixel(_MLXHandler.getImage(), pixelX, pixelY, color);
                    }
                }
            }
        }
    }
}

void FDF::drawLines() {
    int screenCenterX = _MLXHandler.getWidth() / 2;
    int screenCenterY = _MLXHandler.getHeight() / 2;
    
    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            int z = getZ(x, y);
            int drawX = x * _spacing;
            int drawY = y * _spacing;
            
            // Project the point
            std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, z);
            
            // Apply horizontal and vertical offsets first (for centering)
            int centeredX = projectedPoint.first + _horizontalOffset;
            int centeredY = projectedPoint.second + _verticalOffset;
            
            // Then apply camera position and zoom relative to screen center
            int screenX = screenCenterX + ((centeredX - screenCenterX) - _cameraX) * _zoomLevel;
            int screenY = screenCenterY + ((centeredY - screenCenterY) - _cameraY) * _zoomLevel;
            
            // Apply jittering effect
            std::pair<int, int> screenPoint = {screenX, screenY};
            auto jitteredPoint = _vfx->jitter(screenPoint);
            
            int finalX = jitteredPoint.first;
            int finalY = jitteredPoint.second;
            std::pair<int, int> finalPoint = {finalX, finalY};
            
            if (x + 1 < _matrixWidth) {
                int nextZ = getZ(x + 1, y);
                int nextX = (x + 1) * _spacing;
                int nextY = y * _spacing;
                
                std::pair<int, int> nextProjected = _projector->getProjection()->project(nextX, nextY, nextZ);
                
                // Apply the same transformations to the next point
                int nextCenteredX = nextProjected.first + _horizontalOffset;
                int nextCenteredY = nextProjected.second + _verticalOffset;
                
                // Use consistent variable notation (_cameraX or *cameraX, but be consistent)
                int nextScreenX = screenCenterX + ((nextCenteredX - screenCenterX) - _cameraX) * _zoomLevel;
                int nextScreenY = screenCenterY + ((nextCenteredY - screenCenterY) - _cameraY) * _zoomLevel;
                
                std::pair<int, int> nextScreenPoint = {nextScreenX, nextScreenY};
                auto nextJitteredPoint = _vfx->jitter(nextScreenPoint);
                
                std::pair<int, int> nextFinal = {nextJitteredPoint.first, nextJitteredPoint.second};
                
                // Make the bounds checking consistent
                if ((finalX >= 0 && finalX < _MLXHandler.getWidth() && finalY >= 0 && finalY < _MLXHandler.getHeight()) ||
                    (nextFinal.first >= 0 && nextFinal.first < _MLXHandler.getWidth() && 
                     nextFinal.second >= 0 && nextFinal.second < _MLXHandler.getHeight())) {
                    int color1 = getColorFromHeight(z);           // Use current z
                    int color2 = getColorFromHeight(nextZ);       // Use next z
                    drawLineSafeWithGradient(finalPoint, nextFinal, color1, color2);
                }
            }
            
            // Draw vertical line (if not at last row)
            if (y + 1 < _matrixHeight) {
                int nextZ = getZ(x, y + 1);
                int nextX = x * _spacing;
                int nextY = (y + 1) * _spacing;
                
                std::pair<int, int> nextProjected = _projector->getProjection()->project(nextX, nextY, nextZ);
                
                // Apply the same transformations to the next point
                int nextCenteredX = nextProjected.first + _horizontalOffset;
                int nextCenteredY = nextProjected.second + _verticalOffset;
                
                int nextScreenX = screenCenterX + ((nextCenteredX - screenCenterX) - _cameraX) * _zoomLevel;
                int nextScreenY = screenCenterY + ((nextCenteredY - screenCenterY) - _cameraY) * _zoomLevel;
                
                std::pair<int, int> nextScreenPoint = {nextScreenX, nextScreenY};
                auto nextJitteredPoint = _vfx->jitter(nextScreenPoint);
                
                std::pair<int, int> nextFinal = {nextJitteredPoint.first, nextJitteredPoint.second};
                
                // Only draw line if at least one endpoint is within bounds
                if ((finalX >= 0 && finalX < _MLXHandler.getWidth() && finalY >= 0 && finalY < _MLXHandler.getHeight()) ||
                    (nextFinal.first >= 0 && nextFinal.first < _MLXHandler.getWidth() && 
                     nextFinal.second >= 0 && nextFinal.second < _MLXHandler.getHeight())) {
                    int startColor = getColorFromHeight(z);       // Use current z
                    int endColor = getColorFromHeight(nextZ);     // Use next z
                    drawLineSafeWithGradient(finalPoint, nextFinal, startColor, endColor);
                }
            }
        }
    }
}

void FDF::drawLine(std::pair<int, int> start, std::pair<int, int> end, int z1, int z2) {
	double dx = end.first - start.first;
	double dy = end.second - start.second;
	double steps = std::max(std::abs(dx), std::abs(dy));

	double xInc = dx / steps;
	double yInc = dy / steps;

	double x = start.first;
	double y = start.second;

    for (int i = 0; i <= steps; i++) {
        float t = static_cast<float>(i) / steps;
        int color = interpolateColor(getColorFromHeight(z1), getColorFromHeight(z2), t);
        if (x >= 0 && x < _MLXHandler.getWidth() && y >= 0 && y < _MLXHandler.getHeight())
		    mlx_put_pixel(_MLXHandler.getImage(), x, y, color);
		x += xInc;
		y += yInc;
	}
}

void FDF::drawLineSafeWithGradient(std::pair<int, int> start, std::pair<int, int> end, int startColor, int endColor) {
    int x1 = start.first;
    int y1 = start.second;
    int x2 = end.first;
    int y2 = end.second;
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;
    
    // Calculate total distance for gradient
    float totalDistance = sqrt(dx * dx + dy * dy);
    float currentDistance = 0.0f;
    
    // Add this check for equal colors or very small distance
    bool useGradient = (startColor != endColor) && (totalDistance > 0.001f);
    
    int x = x1;
    int y = y1;
    
    while (true) {
        if (x >= 0 && x < _MLXHandler.getWidth() && y >= 0 && y < _MLXHandler.getHeight()) {
            int color;
            if (useGradient) {
                // Calculate gradient percentage
                float t = currentDistance / totalDistance;
                color = interpolateColor(startColor, endColor, t);
            } else {
                // Use start color for the entire line
                color = startColor;
            }
            mlx_put_pixel(_MLXHandler.getImage(), x, y, color);
        }
        
        if (x == x2 && y == y2) break;
        
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
        
        // Update current distance only if we're doing gradient
        if (useGradient) {
            currentDistance = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
        }
    }
}

void FDF::zoom(double factor, int mouseX, int mouseY){
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

void FDF::pan(int dx, int dy){
    _cameraX += dx / _zoomLevel;
    _cameraY += dy / _zoomLevel;
}

void FDF::centerCamera(){
    // Find the minimum and maximum projected coordinates
    int minX = INT_MAX, minY = INT_MAX;
    int maxX = INT_MIN, maxY = INT_MIN;
    
    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            int z = getZ(x, y);
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

//Point color calculations
void FDF::calculateHeightExtremes(){
    _minHeight = INT_MAX;
    _maxHeight = INT_MIN;

    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            // Get the actual z value that will be used for rendering
            int z = getZ(x, y);
            if (z < _minHeight)
                _minHeight = z;
            if (z > _maxHeight)
                _maxHeight = z;
        }
    }
}

float FDF::normalizeHeight(int z) const{
    // Ensure we don't divide by zero
    if (_maxHeight == _minHeight) {
        return 0.5f; // Return middle value if all heights are the same
    }
    
    // Normalize z to a value between 0.0 and 1.0
    return (static_cast<float>(z - _minHeight) / (_maxHeight - _minHeight));
}
//Line color calculations
int FDF::interpolateColor(int color1, int color2, float t) {
    // Clamp t to [0.0, 1.0] range
    t = std::max(0.0f, std::min(1.0f, t));
    
    // Extract individual color channels
    int a1 = (color1 >> 24) & 0xFF;
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;
    
    int a2 = (color2 >> 24) & 0xFF;
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;
    
    // Linear interpolation between colors
    int a = static_cast<int>(a1 + t * (a2 - a1));
    int r = static_cast<int>(r1 + t * (r2 - r1));
    int g = static_cast<int>(g1 + t * (g2 - g1));
    int b = static_cast<int>(b1 + t * (b2 - b1));

    a = std::max(0, std::min(255, a));
    r = std::max(0, std::min(255, r));
    g = std::max(0, std::min(255, g));
    b = std::max(0, std::min(255, b));
    
    // Combine components into a single color
    return (a << 24) | (r << 16) | (g << 8) | b;
}

int FDF::getColorFromHeight(int z){
    float normalized = normalizeHeight(z);

    // 10-color gradient (from lowest to highest)
    uint32_t colors[10] = {
        0x2B3042ff, // Deep navy blue (lowest points, shadows)
        0x495867ff, // Slate blue
        0x748CABff, // Dusty sky blue
        0xAFC1D6ff, // Pale periwinkle
        0xD9E4F5ff, // Light cloud blue
        0xF2E9E4ff, // Soft peach white
        0xF4C095ff, // Warm sand
        0xE57A44ff, // Terracotta orange
        0xB85042ff, // Burnt coral
        0x873D34ff  // Dark red clay (highest peaks)
    };

    // Ensure the normalized value is between 0 and 1
    normalized = std::max(0.0f, std::min(1.0f, normalized));

    // Determine the index in the gradient
    int segment = (int)(normalized * (sizeof(colors) / sizeof(colors[0]) - 1));

    // Get the two colors to interpolate between
    int colorA = colors[segment];
    int colorB = colors[std::min(segment + 1, (int)(sizeof(colors) / sizeof(colors[0]) - 1))];

    // Interpolation factor between the two colors
    float localT = (normalized * (sizeof(colors) / sizeof(colors[0]) - 1)) - segment;

    return interpolateColor(colorA, colorB, localT);
}

//Debug methods
void FDF::printMatrix() const {
    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            std::cout << getZ(x, y) << " ";
        }
        std::cout << std::endl;
    }
}