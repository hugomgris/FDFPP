/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:27:00 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/28 17:08:16 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/UI.hpp"

// Constructor and destructor
UI::UI(MLXHandler *mlxhandler, int uiWidth, int uiHeight)
	: _MLXHandler(mlxhandler), _uiWidth(uiWidth), _uiHeight(uiHeight) {
	
	_controlsOffset = _uiHeight * 0.05;  // 5% from the top
	_interlineSpacing = 30;  // Small, consistent spacing between lines

	_controls = {
		"----CONTROLS----",
		"MOVEMENT:  , , , ",
		"ROTATION:  , ",
		"ZOOM:  ,  /        ",
		"HEIGHT:   ,",
		"RESET: ",
		"EXIT: ",
		" ",
		"----EFFECTS (ON/OFF)----",
		"AUTOROTATE: ",
		"JITTERING: ",
		"WAVEDIST: ",
		"GLITCH: ",
		"PULSEWAVE: ",
		"VORTEXDIST: ",
		" ",
		" ",
		"----PROJECTIONS----",
		"ISOMETRIC: ",
		"ONEPOINT: ",
		"ORTHOGRAPHIC: ",
		"TRIMETRIC: ",
		"DIMETRIC: ",
		"CABINET: ",
		"CAVALIER: ",
		"MILITARY: ",
		"RECURSIVE-DEPTH: ",
		"HYPERBOLIC: ",
	};

	_controls2 = {
		" ",
		"          W A S D",
		"          Q E",
		"      - +   Scroll",
		"        UP DOWN",
		"       R",
		"      ESC",
		" ",
		" ",
		"            1",
		"           2",
		"          3",
		"        4",
		"           5",
		"            6",
		" ",
		" ",
		" ",
		"           F1",
		"          F2",
		"              F3",
		"           F4",
		"          F5",
		"         F6",
		"          F7",
		"          F8",
		"                 F9",
		"            F10",
	};
}

UI::~UI() {}

// Getters
mlx_image_t *UI::getUI() const{ return (_MLXHandler->getUI()); }

// Methods
void UI::fillBackground() {
	uint8_t greyValue = 128; 
	uint8_t opacity = 120;

	// Iterate through each pixel of the image
	for (int y = 0; y < _uiHeight; ++y) {
		for (int x = 0; x < _uiWidth; ++x) {

			mlx_put_pixel(_MLXHandler->getUI(), x, y, 
				(greyValue << 24) |  // Red component 
				(greyValue << 16) |  // Green component
				(greyValue << 8)  |  // Blue component
				opacity             // Alpha/Opacity component
			);
		}
	}
}

void UI::outputControls() {
	// Clear any existing texts first
	clearTexts();

	// Add texts
	for (size_t i = 0; i < _controls.size(); ++i) {
		mlx_image_t *textImage1 = _MLXHandler->getText1();
		textImage1 = mlx_put_string(_MLXHandler->getMLX(), _controls[i].c_str(), 20, _controlsOffset + (_interlineSpacing * i));

		mlx_image_t *textImage2 = _MLXHandler->getText2();
		textImage2 = mlx_put_string(_MLXHandler->getMLX(), _controls2[i].c_str(), 20, _controlsOffset + (_interlineSpacing * i));
		ColorText(textImage2, 160, 235, 255);
		
		if (textImage1) {
			_textImages.push_back(textImage1);
		}

		if (textImage2) {
			_textImages.push_back(textImage2);
		}
	}
}

/*
Pastel pink: (203, 192, 255)
Pastel blue: (230, 216, 173)
Pastel green: (170, 240, 170)
Pastel purple: (230, 190, 230)
Pastel orange: (160, 200, 255)
*/

void UI::ColorText(mlx_image_t *img, uint8_t targetR, uint8_t targetG, uint8_t targetB) {
    if (!img) return;

    uint32_t *pixels = reinterpret_cast<uint32_t*>(img->pixels);
	
    for (uint32_t y = 0; y < img->height; y++) {
        for (uint32_t x = 0; x < img->width; x++) {
            uint32_t idx = y * img->width + x;
            uint32_t pixel = pixels[idx];
            uint8_t a = (pixel >> 24) & 0xFF;
           
            if (a > 0) {
                uint32_t new_pixel =
                    (a << 24) |       // Alpha
                    (targetR << 16) | // Red
                    (targetG << 8) |  // Green
                    (targetB);        // Blue
               
                pixels[idx] = new_pixel;
            }
        }
    }
}

// Method to clear text images
void UI::clearTexts() {
	for (auto textImg : _textImages) {
		if (textImg) {
			mlx_delete_image(_MLXHandler->getMLX(), textImg);
		}
	}
	_textImages.clear();
}