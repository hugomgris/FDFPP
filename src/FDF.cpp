#include "../includes/FDF.hpp"

FDF::FDF(std::vector<std::string> &map, Projector *projector, MLXHandler &MLXHandler, VFX *vfx)
    : _heightMap(map),
      _projector(projector),
      _vfx(vfx),
      _camera(MLXHandler, projector, _heightMap),
      _colorManager(_heightMap),
      _renderer(MLXHandler, _heightMap, _camera, _colorManager, vfx) {
}

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
 * @brief Renders the heightmap with current transformations.
 */
void FDF::draw() {
    _renderer.draw();
}

void FDF::zoom(double factor, int mouseX, int mouseY) {
    _camera.zoom(factor, mouseX, mouseY);
}

void FDF::pan(int dx, int dy) {
    _camera.pan(dx, dy);
}

void FDF::centerCamera() {
    _camera.centerCamera();
}

void FDF::setZFactor(double increase, int mode) {
    _heightMap.setZFactor(increase, mode);
}

void FDF::rotateX(double angle) {
    _camera.rotateX(angle);
}

void FDF::rotateY(double angle) {
    _camera.rotateY(angle);
}

void FDF::rotateZ(double angle) {
    _camera.rotateZ(angle);
}