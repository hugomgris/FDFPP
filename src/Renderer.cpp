/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:43:26 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/18 17:47:40 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Renderer.hpp"
#include <cmath>

Renderer::Renderer(MLXHandler &MLXHandler, HeightMap &heightMap, Camera &camera, 
                   ColorManager &colorManager, VFX *vfx)
    : _MLXHandler(MLXHandler), _heightMap(heightMap), _camera(camera), 
      _colorManager(colorManager), _vfx(vfx) {
}

Renderer::~Renderer() {
}

void Renderer::draw() {
    drawPoints();
    drawLines();
    //mlx_image_to_window(_MLXHandler.getMLX(), _MLXHandler.getImage(), 0, 0);
}

void Renderer::drawPoints() {
    int pointSize = 2;
    
    for (int y = 0; y < _heightMap.getMatrixHeight(); y++) {
        for (int x = 0; x < _heightMap.getMatrixWidth(); x++) {
            int z = _heightMap.getZ(x, y);
            
            // Get screen coordinates
            std::pair<int, int> screenPoint = _camera.worldToScreen(x, y, z);
            
            // Apply jittering effect
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
                        // Get color based on height
                        int color = _colorManager.getColorFromHeight(z);
                        mlx_put_pixel(_MLXHandler.getImage(), pixelX, pixelY, color);
                    }
                }
            }
        }
    }
}

void Renderer::drawLines() {
    for (int y = 0; y < _heightMap.getMatrixHeight(); y++) {
        for (int x = 0; x < _heightMap.getMatrixWidth(); x++) {
            int z = _heightMap.getZ(x, y);
            
            // Get screen coordinates
            std::pair<int, int> screenPoint = _camera.worldToScreen(x, y, z);
            
            // Apply jittering effect
            auto jitteredPoint = _vfx->jitter(screenPoint);
            
            std::pair<int, int> finalPoint = {jitteredPoint.first, jitteredPoint.second};
            
            // Draw horizontal line (if not at last column)
            if (x + 1 < _heightMap.getMatrixWidth()) {
                int nextZ = _heightMap.getZ(x + 1, y);
                
                // Get screen coordinates for next point
                std::pair<int, int> nextScreenPoint = _camera.worldToScreen(x + 1, y, nextZ);
                
                // Apply jittering
                auto nextJitteredPoint = _vfx->jitter(nextScreenPoint);
                
                std::pair<int, int> nextFinal = {nextJitteredPoint.first, nextJitteredPoint.second};
                
                // Only draw line if at least one endpoint is within bounds
                if ((finalPoint.first >= 0 && finalPoint.first < _MLXHandler.getWidth() && 
                     finalPoint.second >= 0 && finalPoint.second < _MLXHandler.getHeight()) ||
                    (nextFinal.first >= 0 && nextFinal.first < _MLXHandler.getWidth() && 
                     nextFinal.second >= 0 && nextFinal.second < _MLXHandler.getHeight())) {
                    int color1 = _colorManager.getColorFromHeight(z);
                    int color2 = _colorManager.getColorFromHeight(nextZ);
                    drawLineSafeWithGradient(finalPoint, nextFinal, color1, color2);
                }
            }
            
            // Draw vertical line (if not at last row)
            if (y + 1 < _heightMap.getMatrixHeight()) {
                int nextZ = _heightMap.getZ(x, y + 1);
                
                // Get screen coordinates for next point
                std::pair<int, int> nextScreenPoint = _camera.worldToScreen(x, y + 1, nextZ);
                
                // Apply jittering
                auto nextJitteredPoint = _vfx->jitter(nextScreenPoint);
                
                std::pair<int, int> nextFinal = {nextJitteredPoint.first, nextJitteredPoint.second};
                
                // Only draw line if at least one endpoint is within bounds
                if ((finalPoint.first >= 0 && finalPoint.first < _MLXHandler.getWidth() && 
                     finalPoint.second >= 0 && finalPoint.second < _MLXHandler.getHeight()) ||
                    (nextFinal.first >= 0 && nextFinal.first < _MLXHandler.getWidth() && 
                     nextFinal.second >= 0 && nextFinal.second < _MLXHandler.getHeight())) {
                    int startColor = _colorManager.getColorFromHeight(z);
                    int endColor = _colorManager.getColorFromHeight(nextZ);
                    drawLineSafeWithGradient(finalPoint, nextFinal, startColor, endColor);
                }
            }
        }
    }
}

void Renderer::drawLineSafeWithGradient(std::pair<int, int> start, std::pair<int, int> end, 
                                        int startColor, int endColor) {
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
                color = _colorManager.interpolateColor(startColor, endColor, t);
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