/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:06:16 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/27 12:20:18 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Getters
Projector *FDF::getProjector() {
    return _projector;
}

VFX *FDF::getVFX() {
    return _vfx;
}

double FDF::getZFactor() {
    return _heightMap.getZFactor();
}

std::vector<std::vector<int>> &FDF::getMatrix() {
    return _heightMap.getMatrix();
}

// Methods
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

void FDF::rotate(double angle) {
    _camera.rotate(angle);
}