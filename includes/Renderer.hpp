/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:19 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/18 17:41:21 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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