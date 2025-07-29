/**
 * @class Camera
 * @brief Controls the rendering viewport and transformations for a height map.
 *
 * This class manages camera transformations such as zoom, pan, rotation, and spacing,
 * and computes projection-related offsets to correctly position the rendered map
 * within the viewport.
 */

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

        void zoom(double factor, int mouseX, int mouseY);
        void pan(int dx, int dy);
        void centerCamera();
        void calculateOffset();
        void calculateInitialScale();
        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);
        
        double getZoomLevel() const;
        int getCameraX() const;
        int getCameraY() const;
        int getHorizontalOffset() const;
        int getVerticalOffset() const;
        double getSpacing() const;
        double getRotationAngleX() const;
        double getRotationAngleY() const;
        double getRotationAngleZ() const;

        std::pair<int, int> worldToScreen(int x, int y, int z) const;

        void reset();
};

#endif