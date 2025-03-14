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
                        mlx_put_pixel(_MLXHandler.getImage(), pixelX, pixelY, 0xFFFFFFFF);
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
            
            // Draw horizontal line (if not at last column)
            if (x + 1 < _matrixWidth) {
                int nextZ = getZ(x + 1, y);
                int nextX = (x + 1) * _spacing;
                int nextY = y * _spacing;
                
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
                    drawLineSafe(finalPoint, nextFinal, 0xFFFFFFFF);
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
                    drawLineSafe(finalPoint, nextFinal, 0xFFFFFFFF);
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
        (void)z1;
        (void)z2;
        //float t = static_cast<float>(i) / steps;
        //int color = interpolateColor(getColorFromHeight(z1), getColorFromHeight(z2), t);
        if (x >= 0 && x < _MLXHandler.getWidth() && y >= 0 && y < _MLXHandler.getHeight())
		    mlx_put_pixel(_MLXHandler.getImage(), x, y, 0xFFFFFFFF);
		x += xInc;
		y += yInc;
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

void FDF::drawLineSafe(std::pair<int, int> start, std::pair<int, int> end, int color) {
    double dx = end.first - start.first;
    double dy = end.second - start.second;
    double steps = std::max(std::abs(dx), std::abs(dy));
    
    if (steps < 1) return; // Don't draw extremely short lines
    
    double xInc = dx / steps;
    double yInc = dy / steps;
    
    double x = start.first;
    double y = start.second;
    
    for (int i = 0; i <= steps; i++) {
        // Check if the pixel is within the window bounds
        if (x >= 0 && x < _MLXHandler.getWidth() && y >= 0 && y < _MLXHandler.getHeight()) {
            mlx_put_pixel(_MLXHandler.getImage(), x, y, color);
        }
        x += xInc;
        y += yInc;
    }
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

	for (const auto &row : _matrix) {
		for (int z : row) {
			if (z < _minHeight)
				_minHeight = z;
			if (z > _maxHeight)
				_maxHeight = z;
		}
	}
}

float FDF::normalizeHeight(int z) const{
    return (static_cast<float>((z - _minHeight) / (_maxHeight - _minHeight)));
}

int FDF::getColor(int z) const{
    float t = normalizeHeight(z);

	int r = (int)(255 * t);
	int g = (int)(255 * t);
	int b = (int)(255 * (1 - t));

	return ((r << 16) | (g << 8) | b);
}

//Line color calculations
int FDF::interpolateColor(int color1, int color2, float t) {
	int red = ((color1 >> 16) & 0xFF) + t * (((color2 >> 16) & 0xFF) - ((color1 >> 16) & 0xFF));
	int green = ((color1 >> 8) & 0xFF) + t * (((color2 >> 8) & 0xFF) - ((color1 >> 8) & 0xFF));
	int blue = (color1 & 0xFF) + t * ((color2 & 0xFF) - (color1 & 0xFF));

	return (red << 16) | (green << 8) | blue;
}

int FDF::getColorFromHeight(int z){
    float normalized = normalizeHeight(z);

	int lowColor = 0x0000FF;   // Blue
	int midColor = 0xFFFFFF;  // White
	int highColor = 0xFF0000; // Red

	if (normalized < 0.5)
		return interpolateColor(lowColor, midColor, normalized * 2);
	else
		return interpolateColor(midColor, highColor, (normalized - 0.5) * 2);
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