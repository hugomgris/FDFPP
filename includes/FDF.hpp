/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:06:36 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/04/03 14:33:21 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_HPP
#define FDF_HPP

#include "HeightMap.hpp"
#include "Camera.hpp"
#include "ColorManager.hpp"
#include "Renderer.hpp"
#include "projections/Projector.hpp"
#include "MLXHandler.hpp"
#include "VFX.hpp"

class FDF {
    private:
        HeightMap _heightMap;
        Projector *_projector;
        VFX *_vfx;
        Camera _camera;
        ColorManager _colorManager;
        Renderer _renderer;

    public:
        FDF(std::vector<std::string> &map, Projector *projector, MLXHandler &MLXHandler, VFX *vfx);
        ~FDF();
        
        // Main methods
        void draw();
        
        // These methods delegate to the appropriate component
        void zoom(double factor, int mouseX, int mouseY);
        void pan(int dx, int dy);
        void centerCamera();
        void setZFactor(double increase, int mode);
        
        // Getters
        Projector *getProjector();
        Camera *getCamera();
        VFX *getVFX();
        HeightMap *getHeightMap();
        ColorManager *getColorManager();
        double getZFactor();
        std::vector<std::vector<int>> &getMatrix();

        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);
    };

#endif