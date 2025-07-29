/**
 * @file UI.cpp
 * @brief Implements the UI class, which displays controls, info, and overlays in the FDF++ application.
 *
 * The UI class manages the user interface overlay, including control instructions, effect toggles,
 * projection modes, color schemes, and map statistics. It draws background panels and colored text
 * using MLX42 image buffers.
 */

#include "../includes/UI.hpp"

/**
 * @brief Constructs a UI object for displaying overlays and controls.
 *
 * Initializes references to HeightMap and MLXHandler, sets up UI dimensions, and prepares control strings.
 *
 * @param heightMap Pointer to the HeightMap for statistics.
 * @param mlxhandler Pointer to the MLXHandler for image buffers.
 * @param uiWidth Width of the UI overlay.
 * @param uiHeight Height of the UI overlay.
 */
UI::UI(HeightMap *heightMap, MLXHandler *mlxhandler, int uiWidth, int uiHeight)
	: _heightMap(heightMap), _MLXHandler(mlxhandler), _uiWidth(uiWidth), _uiHeight(uiHeight) {
	
	_nPoints = std::to_string(_heightMap->getNPoints());
	_nEdges = std::to_string(_heightMap->getNEdges());

	_controlsOffset = _uiHeight * 0.025;
	_interlineSpacing = 30;

	_controls = {
		" ",
		"			MOVEMENT:  , , ,  /",
		"			ROTATION:  ,  /  ,  /  ,  /",
		"			ZOOM:  ,  /        ",
		"			HEIGHT:   ,",
		"			RESET: ",
		" ",
		"			AUTOROTATE: ",
		"			JITTERING: ",
		"			WAVEDIST: ",
		"			GLITCH: ",
		"			PULSEWAVE: ",
		"			VORTEXDIST: ",
		" ",
		"			ISOMETRIC: ",
		"			ONEPOINT: ",
		"			ORTHOGRAPHIC: ",
		"			TRIMETRIC: ",
		"			DIMETRIC: ",
		"			CABINET: ",
		"			CAVALIER: ",
		"			MILITARY: ",
		"			RECURSIVE-DEPTH: ",
		"			HYPERBOLIC: ",
		"			CONIC: ",
		"			SPHERICAL: ",
		" ",
		"			EARTHVOID: ",
		"			FOREST-MOUNTAIN: ",
		"			CANYONS: ",
		"			LAVA: ",
		"			KRZ: ",
		"			B&W: ",
		" ",
		"			POINTS:       // EDGES:",
	};

	_controls2 = {
		"CONTROLS:",
		"			          W A S D   LMB",
		"			          Q E   I J   K L   RMB",
		"			      - +   Scroll",
		"		         UP DOWN",
		"			       R",
		"EFFECTS:",
		"			            1",
		"			           2",
		"			          3",
		"			        4",
		"			           5",
		"			            6",
		"PROJECTIONS:",
		"			           F1",
		"			          F2",
		"			              F3",
		"			           F4",
		"			          F5",
		"			         F6",
		"			          F7",
		"			          F8",
		"			                 F9",
		"			            F10",
		"			       F11",
		"			           F12",
		"COLORS:",
		"			           KP-1",
		"			                 KP-2",
		"			         KP-3",
		"			      KP-4",
		"			     KP-5",
		"			     KP-6",
		"INFO:",
		"			        " + _nPoints + "            " + _nEdges,
	};
}

/**
 * @brief Destructor for UI. Cleans up UI resources if needed.
 */
UI::~UI() {}

mlx_image_t *UI::getUI() const{ return (_MLXHandler->getUI()); }

/**
 * @brief Fills the UI background with a semi-transparent grey color.
 *
 * Iterates over the UI image buffer and sets each pixel to the background color.
 */
void UI::fillBackground() {
	uint8_t greyValue = 128; 
	uint8_t opacity = 120;

	for (int y = 0; y < _uiHeight; ++y) {
		for (int x = 0; x < _uiWidth; ++x) {

			mlx_put_pixel(_MLXHandler->getUI(), x, y, 
				(greyValue << 24) |
				(greyValue << 16) |
				(greyValue << 8)  |
				opacity
			);
		}
	}
}

/**
 * @brief Outputs control instructions, effect toggles, and info to the UI overlay.
 *
 * Draws control and info strings to the UI image buffer and colors the text.
 */
void UI::outputControls() {
	clearTexts();

	for (size_t i = 0; i < _controls.size(); ++i) {
		mlx_image_t *textImage1 = _MLXHandler->getText1();
		textImage1 = mlx_put_string(_MLXHandler->getMLX(), _controls[i].c_str(), 20, _controlsOffset + (_interlineSpacing * i));

		mlx_image_t *textImage2 = _MLXHandler->getText2();
		textImage2 = mlx_put_string(_MLXHandler->getMLX(), _controls2[i].c_str(), 20, _controlsOffset + (_interlineSpacing * i));
		ColorText(textImage2, 140, 200, 255);
		
		if (textImage1) {
			_textImages.push_back(textImage1);
		}

		if (textImage2) {
			_textImages.push_back(textImage2);
		}
	}
}

/**
 * @brief Colors the text in a given MLX image buffer with the specified RGB values.
 *
 * Iterates over the image pixels and applies the target color to non-transparent text pixels.
 *
 * @param img Pointer to the MLX image buffer containing text.
 * @param targetR Target red value.
 * @param targetG Target green value.
 * @param targetB Target blue value.
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
					(a << 24) |
					(targetR << 16) |
					(targetG << 8) |
					(targetB);
			   
				pixels[idx] = new_pixel;
			}
		}
	}
}

/**
 * @brief Clears all text images from the UI overlay and deletes their buffers.
 *
 * Iterates over stored text image pointers and deletes them from the MLX context.
 */
void UI::clearTexts() {
	for (auto textImg : _textImages) {
		if (textImg) {
			mlx_delete_image(_MLXHandler->getMLX(), textImg);
		}
	}
	_textImages.clear();
}