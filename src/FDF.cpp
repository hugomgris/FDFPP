/**
 * @file FDF.cpp
 * @brief Implements the FDF class, which acts as the orchestrator of rendering logic.
 *
 * Connects the HeightMap, Projector, Camera, ColorManager, and Renderer
 * to enable real-time rendering of a wireframe heightmap.
 */

#include "../includes/FDF.hpp"

/**
 * @brief Constructs the FDF rendering system.
 * 
 * Initializes all required components and links them:
 * - HeightMap from raw string map input
 * - Projector for 3D projection
 * - Camera for viewport manipulation
 * - ColorManager for height-based coloring
 * - Renderer to draw the final output
 *
 * @param map The parsed string map data.
 * @param projector Pointer to the active Projector.
 * @param MLXHandler Reference to the MLX handler managing the window.
 * @param vfx Pointer to the active visual effects engine.
 */
FDF::FDF(std::vector<std::string> &map, Projector *projector, MLXHandler &MLXHandler, VFX *vfx)
    : _heightMap(map),
      _projector(projector),
      _vfx(vfx),
      _camera(MLXHandler, projector, _heightMap),
      _colorManager(_heightMap),
      _renderer(MLXHandler, _heightMap, _camera, _colorManager, vfx) {
}

/**
 * @brief Destructor for FDF.
 */
FDF::~FDF() {
}

Projector *FDF::getProjector() {
    return _projector;
}

Camera *FDF::getCamera() {
    return &_camera;
}

VFX *FDF::getVFX() {
    return _vfx;
}

HeightMap *FDF::getHeightMap() {
    return &_heightMap;
}

ColorManager *FDF::getColorManager() {
    return &_colorManager;
}

double FDF::getZFactor() {
    return _heightMap.getZFactor();
}

std::vector<std::vector<int>> &FDF::getMatrix() {
    return _heightMap.getMatrix();
}

/**
 * @brief Renders the current height map using the renderer.
 */
void FDF::draw() {
    _renderer.draw();
}

/**
 * @brief Zooms the camera in or out toward a specific screen point.
 *
 * @param factor Zoom factor to apply.
 * @param mouseX X coordinate of mouse or -1.
 * @param mouseY Y coordinate of mouse or -1.
 */
void FDF::zoom(double factor, int mouseX, int mouseY) {
    _camera.zoom(factor, mouseX, mouseY);
}

/**
 * @brief Moves the camera position by a screen-space offset.
 *
 * @param dx Horizontal pan.
 * @param dy Vertical pan.
 */
void FDF::pan(int dx, int dy) {
    _camera.pan(dx, dy);
}

/**
 * @brief Re-centers the camera on the map.
 */
void FDF::centerCamera() {
    _camera.centerCamera();
}

/**
 * @brief Adjusts the Z-axis scaling factor in the height map.
 *
 * @param increase The amount to change the Z factor.
 * @param mode Whether to increase (+1), decrease (-1), or do nothing (0).
 */
void FDF::setZFactor(double increase, int mode) {
    _heightMap.setZFactor(increase, mode);
}

/**
 * @brief Rotates the camera around the X-axis.
 * @param angle Angle to rotate in radians.
 */
void FDF::rotateX(double angle) {
    _camera.rotateX(angle);
}

/**
 * @brief Rotates the camera around the Y-axis.
 * @param angle Angle to rotate in radians.
 */
void FDF::rotateY(double angle) {
    _camera.rotateY(angle);
}

/**
 * @brief Rotates the camera around the Z-axis.
 * @param angle Angle to rotate in radians.
 */
void FDF::rotateZ(double angle) {
    _camera.rotateZ(angle);
}