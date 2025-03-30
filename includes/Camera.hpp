/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:40:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/27 12:22:37 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "MLXHandler.hpp"
#include "projections/Projector.hpp"
#include "HeightMap.hpp"

class Camera {
    private:
        double _zoomLevel;
        int _cameraX;
        int _cameraY;
        int _horizontalOffset;
        int _verticalOffset;
        double _spacing;
        double _rotationAngleX;
        double _rotationAngleY;
        double _rotationAngleZ;
        MLXHandler &_MLXHandler;
        Projector *_projector;
        HeightMap &_heightMap;

        // Original levels for reset
        double _OriginalZoomLevel;
        int _OriginalCameraX;
        int _OriginalCameraY;
        int _OriginalHorizontalOffset;
        int _OriginalVerticalOffset;
        double _OriginalSpacing;
        double _OriginalRotationAngleX;
        double _OriginalRotationAngleY;
        double _OriginalRotationAngleZ;

    public:
        Camera(MLXHandler &MLXHandler, Projector *projector, HeightMap &heightMap);
        ~Camera();

        // Camera control methods
        void zoom(double factor, int mouseX, int mouseY);
        void pan(int dx, int dy);
        void centerCamera();
        void calculateOffset();
        void calculateInitialScale();
        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);
        
        // Getters
        double getZoomLevel() const;
        int getCameraX() const;
        int getCameraY() const;
        int getHorizontalOffset() const;
        int getVerticalOffset() const;
        double getSpacing() const;
        double getRotationAngleX() const;
        double getRotationAngleY() const;
        double getRotationAngleZ() const;
        
        // Coordinate transformation
        std::pair<int, int> worldToScreen(int x, int y, int z) const;

        // RESET
        void reset();
};

#endif