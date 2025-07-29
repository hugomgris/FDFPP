/**
 * @file Renderer.hpp
 * @brief Declares the Renderer class for drawing the heightmap wireframe and points.
 *
 * The Renderer class exposes methods for rendering map points and edges, applying color gradients,
 * and integrating visual effects. It is designed for real-time interactive visualization.
 */
 
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "MLXHandler.hpp"
#include "HeightMap.hpp"
#include "Camera.hpp"
#include "ColorManager.hpp"
#include "VFX.hpp"

class Renderer {
private:
    MLXHandler &_MLXHandler;
    HeightMap &_heightMap;
    Camera &_camera;
    ColorManager &_colorManager;
    VFX *_vfx;
    float _time;
    
public:
    Renderer(MLXHandler &MLXHandler, HeightMap &heightMap, Camera &camera, 
             ColorManager &colorManager, VFX *vfx);
    ~Renderer();
    
    void draw();
    
private:
    void drawPoints();
    void drawLines();
    void drawLineSafeWithGradient(std::pair<int, int> start, std::pair<int, int> end, 
                                  int startColor, int endColor);
};

#endif