/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColorManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:05 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/04/03 14:25:58 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_MANAGER_HPP
#define COLOR_MANAGER_HPP

#include <cstdint>
#include <algorithm>
#include "HeightMap.hpp"

class ColorManager {
    private:
        HeightMap &_heightMap;
        
        static constexpr uint32_t _colors1[] = {
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

        // Forest & Mountains Palette
        static constexpr uint32_t _colors2[] = {
            0x1A2F38ff, // Deep forest blue (water/valleys)
            0x39444Eff, // Slate gray
            0x5E747Fff, // Muted blue-gray
            0x7A9E7Eff, // Sage green
            0x9EB25Eff, // Olive green
            0xC1C56Aff, // Light olive
            0xDBC077ff, // Wheat
            0xBD8B5Eff, // Tan brown
            0x96624Eff, // Cedar brown
            0x6E392Eff  // Dark auburn (peaks)
        };
        
        // Desert & Canyons Palette
        static constexpr uint32_t _colors3[] = {
            0x0F2C4Aff, // Deep blue (oasis water)
            0x254B7Aff, // Medium blue
            0x4A6D8Cff, // Dusty blue
            0xD19C4Cff, // Sand yellow
            0xDFAC66ff, // Light sand
            0xE8BA81ff, // Pale sand
            0xC67052ff, // Clay orange
            0xA44A3Fff, // Rust
            0x7D3B34ff, // Brick red
            0x582C2Cff  // Dark brown (peaks)
        };
        
        // Volcanic & Lava Palette
        static constexpr uint32_t _colors4[] = {
            0x0E0B16ff, // Dark purple-black (valleys)
            0x221E32ff, // Deep indigo
            0x36304Aff, // Dark slate purple
            0x4A444Cff, // Charcoal
            0x564E4Aff, // Dark ash
            0x7A522Eff, // Bronze
            0xA93E2Eff, // Burnt orange
            0xCC2D2Dff, // Fire red
            0xE83A0Fff, // Bright orange
            0xFFD700ff  // Glowing yellow (peaks/lava)
        };

        static constexpr int COLOR_COUNT = 10;

        const uint32_t* _selectedColors;
        int _currentColorSet;
    
    public:
        ColorManager(HeightMap &heightMap);
        ~ColorManager();
        
        void setColorSet(int colorSetIndex) {
            switch(colorSetIndex) {
                case 0:
                    _selectedColors = _colors1;
                    break;
                case 1:
                    _selectedColors = _colors2;
                    break;
                case 2:
                    _selectedColors = _colors3;
                    break;
                case 3:
                    _selectedColors = _colors4;
                    break;
                default:
                    _selectedColors = _colors1;
                    colorSetIndex = 0;
                    break;
            }
            _currentColorSet = colorSetIndex;
        }
        
        int getCurrentColorSet() const {
            return _currentColorSet;
        }

        int getColorFromHeight(int x, int y, int z);
        int interpolateColor(int color1, int color2, float t);
};

#endif