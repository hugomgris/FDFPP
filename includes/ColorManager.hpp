/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColorManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:05 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/31 09:51:22 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_MANAGER_HPP
#define COLOR_MANAGER_HPP

#include <cstdint>
#include <algorithm>
#include "HeightMap.hpp"

class ColorManager {
public:
    ColorManager(HeightMap &heightMap);
    ~ColorManager();
    
    int getColorFromHeight(int x, int y, int z);
    int interpolateColor(int color1, int color2, float t);
    
private:
    HeightMap &_heightMap;
    
    // Define your color gradient here
    static constexpr uint32_t _colors[] = {
        0x2B3042ff, // Deep navy blue (lowest points, shadows)
        0x495867ff, // Slate blue
        0x748CABff, // Dusty sky blue
        0xAFC1D6ff, // Pale periwinkle
        0xD9E4F5ff, // Light cloud blue
        0xF2E9E4ff, // Soft peach white
        0xF4C095ff, // Warm sand
        0xE57A44ff, // Terracotta orange
        0xB85042ff, // Burnt coral
        0x873D34ff  // Dark red clay (highest peaks)
    };
};

#endif