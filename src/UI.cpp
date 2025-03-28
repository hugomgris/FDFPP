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
UI::UI(MLXHandler *mlxhandler, int uiWidth, int uiHeight): _MLXHandler(mlxhandler), _uiWidth(uiWidth), _uiHeight(uiHeight) {}

UI::~UI() {}

// Getters
mlx_image_t *UI::getUI() const{ return (_MLXHandler->getUI()); }

// Methods
void UI::fillBackground() {
	// Calculate 25% opacity (64 out of 255)
	uint8_t greyValue = 128;  // Mid-grey value
	uint8_t opacity = 64;     // 25% opacity

	// Iterate through each pixel of the image
	for (int y = 0; y < _uiHeight; ++y) {
		for (int x = 0; x < _uiWidth; ++x) {
			// Set pixel color to grey with 25% opacity
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

	// Define control texts
	std::vector<std::string> placeholders = {
		"----CONTROLS----",
		"MOVEMENT:  , , , ",
		"ROTATION:  , ",
		"ZOOM:  ,          ",
		"HEIGHT: "
	};

	std::vector<std::string> placeholders2 = {
		" ",
		"          W A S D",
		"          Q E",
		"      - + / Scroll",
		"        arrows UP, DOWN"
	};


	// Calculate vertical positioning
	int topOffset = _uiHeight * 0.05;  // 5% from the top
	int interlineSpacing = 30;  // Small, consistent spacing between lines

	// Add texts
	for (size_t i = 0; i < placeholders.size(); ++i) {
		mlx_image_t *textImage1 = _MLXHandler->getText1();
		textImage1 = mlx_put_string(_MLXHandler->getMLX(), placeholders[i].c_str(), 20, topOffset + (interlineSpacing * i));

		mlx_image_t *textImage2 = _MLXHandler->getText2();
		textImage2 = mlx_put_string(_MLXHandler->getMLX(), placeholders2[i].c_str(), 20, topOffset + (interlineSpacing * i));
		RedText(textImage2);
		
		if (textImage1) {
			_textImages.push_back(textImage1);
		}

		if (textImage2) {
			_textImages.push_back(textImage2);
		}
	}
}

void UI::RedText(mlx_image_t *img) {
    if (!img) return;
    uint32_t *pixels = reinterpret_cast<uint32_t*>(img->pixels);
    
    for (uint32_t y = 0; y < img->height; y++) {
        for (uint32_t x = 0; x < img->width; x++) {
            uint32_t idx = y * img->width + x;
            uint32_t pixel = pixels[idx];
            uint8_t a = (pixel >> 24) & 0xFF; // Alpha
            
            if (a > 0) {
                // Extract original brightness (R=G=B in grayscale)
                uint8_t brightness = pixel & 0xFF;
                
                // Create red pixel
                uint32_t new_pixel = 
                    (a << 24)     |   // Alpha
                    (brightness << 0) | // Red channel
                    (0x00 << 8)   |   // Green channel
                    (0x00);            // Blue channel
                
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