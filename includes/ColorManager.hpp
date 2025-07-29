/**
 * @class ColorManager
 * @brief Manages color selection and interpolation based on height values.
 *
 * Provides a way to color heightmap points by interpolating between predefined
 * color palettes. Also supports custom per-point colors defined in the HeightMap.
 */
 
#ifndef COLOR_MANAGER_HPP
#define COLOR_MANAGER_HPP

#include <cstdint>
#include <algorithm>
#include "HeightMap.hpp"

class ColorManager {
    private:
        HeightMap &_heightMap;
        
        static constexpr uint32_t _colors1[] = {
            0x2B3042ff,
            0x495867ff,
            0x748CABff,
            0xAFC1D6ff,
            0xD9E4F5ff,
            0xF2E9E4ff,
            0xF4C095ff,
            0xE57A44ff,
            0xB85042ff,
            0x873D34ff
        };

        static constexpr uint32_t _colors2[] = {
            0x1A2F38ff,
            0x39444Eff,
            0x5E747Fff,
            0x7A9E7Eff,
            0x9EB25Eff,
            0xC1C56Aff,
            0xDBC077ff,
            0xBD8B5Eff,
            0x96624Eff,
            0x6E392Eff
        };
        
        static constexpr uint32_t _colors3[] = {
            0x0F2C4Aff,
            0x254B7Aff,
            0x4A6D8Cff,
            0xD19C4Cff,
            0xDFAC66ff,
            0xE8BA81ff,
            0xC67052ff,
            0xA44A3Fff,
            0x7D3B34ff,
            0x582C2Cff
        };
        
        static constexpr uint32_t _colors4[] = {
            0x0E0B16ff,
            0x221E32ff,
            0x36304Aff,
            0x4A444Cff,
            0x564E4Aff,
            0x7A522Eff,
            0xA93E2Eff,
            0xCC2D2Dff,
            0xE83A0Fff,
            0xFFD700ff
        };


        static constexpr uint32_t _colors5[] = {
            0x181A1Bff,
            0x2C2F33ff,
            0x3C4A4Eff,
            0x4B5D6Eff,
            0x6C7A89ff,
            0xA3A9A6ff,
            0xC9B89Aff,
            0xE3C77Aff,
            0xE8A87Aff,
            0xF7F7F7ff
        };

        static constexpr uint32_t _colors6[] = {
            0x000000ff,
            0x222222ff,
            0x444444ff,
            0x666666ff,
            0x888888ff,
            0xAAAAAAff,
            0xCCCCCCff,
            0xEEEEEEff,
            0xF7F7F7ff,
            0xFFFFFFFF
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
                case 4:
                    _selectedColors = _colors5;
                    break;
                case 5:
                    _selectedColors = _colors6;
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