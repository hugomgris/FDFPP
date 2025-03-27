/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:27:00 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/27 16:52:32 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/UI.hpp"

// Constructor and destructor
UI::UI(mlx_t *mlx, mlx_image_t *ui, int uiWidth, int uiHeight): _mlx(mlx), _ui(ui), _uiWidth(uiWidth), _uiHeight(uiHeight) {}

UI::~UI() {}

// Getters
mlx_image_t *UI::getUI() const{ return (_ui); }

// Methods
void UI::fillBackground() {
	// Calculate 25% opacity (64 out of 255)
	uint8_t greyValue = 128;  // Mid-grey value
	uint8_t opacity = 64;     // 25% opacity

	// Iterate through each pixel of the image
	for (int y = 0; y < _uiHeight; ++y) {
		for (int x = 0; x < _uiWidth; ++x) {
			// Set pixel color to grey with 25% opacity
			mlx_put_pixel(_ui, x, y, 
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
		"MOVEMENT: W,A,S,D",
		"ROTATION: Q,E",
		"ZOOM: -,+ / Scroll",
		"HEIGHT: arrows UP, DOWN"
	};

	// Calculate vertical positioning
	int topOffset = _uiHeight * 0.05;  // 5% from the top
	int interlineSpacing = 30;  // Small, consistent spacing between lines

	// Add texts
	for (size_t i = 0; i < placeholders.size(); ++i) {
		mlx_image_t* textImage = mlx_put_string(_mlx, placeholders[i].c_str(), 20, topOffset + (interlineSpacing * i));
		
		if (textImage) {
			_textImages.push_back(textImage);
		}
	}
}

// Method to clear text images
void UI::clearTexts() {
	for (auto textImg : _textImages) {
		if (textImg) {
			mlx_delete_image(_mlx, textImg);
		}
	}
	_textImages.clear();
}