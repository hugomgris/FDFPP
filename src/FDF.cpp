/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:06:16 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 16:35:29 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.hpp"

//Constructor and destructor
FDF::FDF(std::vector<std::string> &map, Projector *projector, MLXHandler &MLXHandler): 
	_projector(projector), _MLXHandler(MLXHandler){
		for (const std::string & line : map){
			std::istringstream iss(line);
			std::vector<int> row;

			int value;
			while (iss >> value){
				row.push_back(value);
			}
			_matrix.push_back(row);
		}

		_matrixHeight = _matrix.size();
		_matrixWidth = _matrix[0].size();
		_spacing = 20;
}

FDF::~FDF(){}

//Getters
std::vector<std::vector<int>> &FDF::getMatrix(){
	return (_matrix);
}

Projector *FDF::getProjector(){
    return (_projector);
}

//Methods
int FDF::getZ(int x, int y) const{
    if (y < 0 || y >= _matrixHeight || x < 0 || x >= _matrixWidth)
        return (0);
    return (_matrix[y][x]);
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

void FDF::draw() {
	drawPoints();
	drawLines();
	mlx_image_to_window(_MLXHandler.getMLX(), _MLXHandler.getImage(), 0, 0);
}

void FDF::drawPoints() {
    calculateOffset();
    int pointSize = 2;
    
    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            int z = getZ(x, y);
            int drawX = x * _spacing; // No offset here
            int drawY = y * _spacing; // No offset here
            
            // Project first, then apply offset
            std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, z);
            int finalX = projectedPoint.first + _horizontalOffset;
            int finalY = projectedPoint.second + _verticalOffset;
            
            // Draw point
            for (int i = -pointSize / 2; i <= pointSize / 2; i++) {
                for (int j = -pointSize / 2; j <= pointSize / 2; j++) {
                    mlx_put_pixel(_MLXHandler.getImage(), finalX + i, finalY + j, 0xFFFFFF);
                }
            }
        }
    }
}

void FDF::drawLines() {
    for (int y = 0; y < _matrixHeight; y++) {
        for (int x = 0; x < _matrixWidth; x++) {
            int z = getZ(x, y);
            int drawX = x * _spacing; // No offset here
            int drawY = y * _spacing; // No offset here
            
            // Project first, then apply offset
            std::pair<int, int> projectedPoint = _projector->getProjection()->project(drawX, drawY, z);
            std::pair<int, int> finalPoint = {
                projectedPoint.first + _horizontalOffset,
                projectedPoint.second + _verticalOffset
            };
            
            // Draw horizontal line (if not at last column)
            if (x + 1 < _matrixWidth) {
                int nextZ = getZ(x + 1, y);
                int nextX = (x + 1) * _spacing;
                int nextY = y * _spacing;
                
                std::pair<int, int> nextProjected = _projector->getProjection()->project(nextX, nextY, nextZ);
                std::pair<int, int> nextFinal = {
                    nextProjected.first + _horizontalOffset,
                    nextProjected.second + _verticalOffset
                };
                
                drawLine(finalPoint, nextFinal, 0xFFFFFF);
            }
            
            // Draw vertical line (if not at last row)
            if (y + 1 < _matrixHeight) {
                int nextZ = getZ(x, y + 1);
                int nextX = x * _spacing;
                int nextY = (y + 1) * _spacing;
                
                std::pair<int, int> nextProjected = _projector->getProjection()->project(nextX, nextY, nextZ);
                std::pair<int, int> nextFinal = {
                    nextProjected.first + _horizontalOffset,
                    nextProjected.second + _verticalOffset
                };
                
                drawLine(finalPoint, nextFinal, 0xFFFFFF);
            }
        }
    }
}

void FDF::drawLine(std::pair<int, int> start, std::pair<int, int> end, int color) {
	double dx = end.first - start.first;
	double dy = end.second - start.second;
	double steps = std::max(std::abs(dx), std::abs(dy));

	double xInc = dx / steps;
	double yInc = dy / steps;

	double x = start.first;
	double y = start.second;

	for (int i = 0; i <= steps; i++) {
		mlx_put_pixel(_MLXHandler.getImage(), x, y, color);
		x += xInc;
		y += yInc;
	}
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