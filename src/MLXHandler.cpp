/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:54:44 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/07/28 15:18:42 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MLXHandler.hpp"
#include "../includes/FDF.hpp"

//Constructors and destructor
MLXHandler::MLXHandler(int width, int height, const char *title)
    : _width(width), _height(height), _title(title), _autoRotate(false),
      _leftMousePressed(false), _rightMousePressed(false), _lastMouseX(0), _lastMouseY(0) {
	this->_mlx = mlx_init(this->_width, this->_height, this->_title, true);

	if (!this->_mlx)
		throw std::runtime_error("MLX failed to initialize");
	
	if (!this->_mlx->window) {
	throw std::runtime_error("MLX initialized but window is NULL! Check OpenGL support.");
    }
	
    _uiWidth = _width / 5;
    _uiHeight = _height;


	this->_img = mlx_new_image(this->_mlx, this->_width, this->_height);
	if (!this->_img){
		throw std::runtime_error("Failed to create image buffer");
	}

    this->_ui = mlx_new_image(this->_mlx, this->_uiWidth, this->_uiHeight);
	if (!this->_ui){
		throw std::runtime_error("Failed to create UI buffer");
	}

    mlx_image_to_window(this->_mlx, this->_img, 0, 0);
    mlx_image_to_window(this->_mlx, this->_ui, 0, 0);
}

MLXHandler::MLXHandler(const MLXHandler &other): _title(other._title){
	*this = other;
}

MLXHandler::~MLXHandler() {}

//Operator overload
MLXHandler &MLXHandler::operator=(const MLXHandler &other){
	if (this != &other){
		this->_width = other._width;
		this->_height = other._height;
		this->_mlx = other._mlx;
		this->_img = other._img;
	}

	return (*this);
}

//Getters & Setters
int &MLXHandler::getHeight(){
	return (_height);
}

int &MLXHandler::getWidth(){
	return (_width);
}

int &MLXHandler::getUIWidth(){
	return (_uiWidth);
}

int &MLXHandler::getUIHeight(){
	return (_uiHeight);
}

mlx_image_t *MLXHandler::getImage() const{
	return (_img);
}

mlx_image_t *MLXHandler::getUI() const{
    return (_ui);
}

mlx_image_t *MLXHandler::getText1() const{
    return (_text1);
}

mlx_image_t *MLXHandler::getText2() const{
    return (_text2);
}

mlx_t *MLXHandler::getMLX() const{
	return (_mlx);
}

FDF *MLXHandler::getFDF() const{
    return (_fdf);
}

bool &MLXHandler::getAutoRotate(){
    return (_autoRotate);
}
void MLXHandler::setAutoRotate(bool autoRotate) { _autoRotate = autoRotate; }

void MLXHandler::setFDF(FDF *fdf){
	_fdf = fdf;
}

//Methods
void MLXHandler::render() const{
	mlx_loop(this->_mlx);
}

void MLXHandler::handleEvents(){
	mlx_loop_hook(_mlx, basicHooks, this);
	mlx_scroll_hook(_mlx, &scrollHook, this);
	mlx_loop_hook(_mlx, perspectiveHooks, this);
    mlx_mouse_hook(_mlx, &mouseHook, this);
}

void MLXHandler::clearImage(mlx_image_t *img){
    (void)img;
	for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            mlx_put_pixel(_img, x, y, 0x000000FF);
        }
    }
}

void MLXHandler::cleanup() {
    if (this->_img && this->_mlx) {
        mlx_delete_image(this->_mlx, this->_img);
        this->_img = nullptr;
    }
    
    if (this->_mlx) {
        mlx_terminate(this->_mlx);
        this->_mlx = nullptr;
    }
}

void MLXHandler::mouseHook(mouse_key_t button, action_t action, modifier_key_t mods, void *param) {
    MLXHandler *self = static_cast<MLXHandler *>(param);
    (void)mods; // Suppress unused parameter warning
    
    int32_t mouseX, mouseY;
    mlx_get_mouse_pos(self->_mlx, &mouseX, &mouseY);
    
    // Track mouse button state
    if (button == MLX_MOUSE_BUTTON_LEFT) {
        if (action == MLX_PRESS) {
            self->_leftMousePressed = true;
            self->_lastMouseX = mouseX;
            self->_lastMouseY = mouseY;
        } else if (action == MLX_RELEASE) {
            self->_leftMousePressed = false;
        }
    } else if (button == MLX_MOUSE_BUTTON_RIGHT) {
        if (action == MLX_PRESS) {
            self->_rightMousePressed = true;
            self->_lastMouseX = mouseX;
            self->_lastMouseY = mouseY;
        } else if (action == MLX_RELEASE) {
            self->_rightMousePressed = false;
        }
    }
}

void MLXHandler::basicHooks(void *param) {
    MLXHandler *self = static_cast<MLXHandler *>(param);
    static int frameCount = 0;
    
    static bool oneKeyWasPressed = false; 
    static bool twoKeyWasPressed = false;
    static bool threeKeyWasPressed = false;
    static bool fourKeyWasPressed = false;
    static bool fiveKeyWasPressed = false;
    static bool sixKeyWasPressed = false;

    static bool PadOneKeyWasPressed = false;
    static bool PadTwoKeyWasPressed = false;
    static bool PadThreeKeyWasPressed = false;
    static bool PadFourKeyWasPressed = false;
    static bool PadFiveKeyWasPressed = false;
    static bool PadSixKeyWasPressed = false;

    bool needsRedraw = false;

    // Handle mouse movement
    if (self->_leftMousePressed || self->_rightMousePressed) {
        int32_t mouseX, mouseY;
        mlx_get_mouse_pos(self->_mlx, &mouseX, &mouseY);
        
        int deltaX = mouseX - self->_lastMouseX;
        int deltaY = mouseY - self->_lastMouseY;
        
        if (self->_leftMousePressed && (deltaX != 0 || deltaY != 0)) {
            self->_fdf->pan(-deltaX, -deltaY);
            needsRedraw = true;
        }
        
        if (self->_rightMousePressed && (deltaX != 0 || deltaY != 0)) {
            self->_fdf->rotateY(deltaX * 0.01);
            self->_fdf->rotateX(deltaY * -0.01);
            needsRedraw = true;
        }
        
        self->_lastMouseX = mouseX;
        self->_lastMouseY = mouseY;
    }

    // Check for window close
    if (mlx_is_key_down(self->_mlx, MLX_KEY_ESCAPE))
        mlx_close_window(self->_mlx);

    // Z-factor adjustment
    if (mlx_is_key_down(self->_mlx, MLX_KEY_UP)) {
        self->_fdf->setZFactor(0.1, 1);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_DOWN)) {
        self->_fdf->setZFactor(0.1, -1);
        needsRedraw = true;
    }

    // Zoom controls
    if (mlx_is_key_down(self->_mlx, MLX_KEY_KP_SUBTRACT)) {
        self->_fdf->zoom(0.9, -1, -1);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_KP_ADD)) {
        self->_fdf->zoom(1.1, -1, -1);
        needsRedraw = true;
    }

    // Panning controls
    if (mlx_is_key_down(self->_mlx, MLX_KEY_A)) {
        self->_fdf->pan(10, 0);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_D)) {
        self->_fdf->pan(-10, 0);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_W)) {
        self->_fdf->pan(0, 10);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_S)) {
        self->_fdf->pan(0, -10);
        needsRedraw = true;
    }

    // Rotation controls
    if (mlx_is_key_down(self->_mlx, MLX_KEY_Q)) {
        self->_fdf->rotateZ(-0.05);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_E)) {
        self->_fdf->rotateZ(0.05);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_I)) {
        self->_fdf->rotateX(0.05);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_J)) {
        self->_fdf->rotateX(-0.05);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_K)) {
        self->_fdf->rotateY(0.05);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_L)) {
        self->_fdf->rotateY(-0.05);
        needsRedraw = true;
    }

    // RESET
    if (mlx_is_key_down(self->_mlx, MLX_KEY_R)) {
        self->_fdf->getCamera()->reset();
        self->_fdf->getCamera()->calculateInitialScale();
        self->_fdf->getCamera()->calculateOffset();
        self->_fdf->getCamera()->centerCamera();
        self->setAutoRotate(false);
        self->_fdf->getVFX()->setJitterStatus(false);
        self->_fdf->getVFX()->setWaveStatus(false);
        self->_fdf->getVFX()->setGlitchStatus(false);
        self->_fdf->getVFX()->setPulseWaveStatus(false);
        self->_fdf->getVFX()->setVortexDistortionStatus(false);
        needsRedraw = true;
    }

    // COLORS
    bool PadOneKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_KP_1);
    if (PadOneKeyIsPressed && !PadOneKeyWasPressed) {
        self->_fdf->getColorManager()->setColorSet(0);
        needsRedraw = true;
    }
    PadOneKeyWasPressed = PadOneKeyIsPressed;

    bool PadTwoKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_KP_2);
    if (PadTwoKeyIsPressed && !PadTwoKeyWasPressed) {
        self->_fdf->getColorManager()->setColorSet(1);
        needsRedraw = true;
    }
    PadTwoKeyWasPressed = PadTwoKeyIsPressed;

    bool PadThreeKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_KP_3);
    if (PadThreeKeyIsPressed && !PadThreeKeyWasPressed) {
        self->_fdf->getColorManager()->setColorSet(2);
        needsRedraw = true;
    }
    PadThreeKeyWasPressed = PadThreeKeyIsPressed;

    bool PadFourKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_KP_4);
    if (PadFourKeyIsPressed && !PadFourKeyWasPressed) {
        self->_fdf->getColorManager()->setColorSet(3);
        needsRedraw = true;
    }
    PadFourKeyWasPressed = PadFourKeyIsPressed;

    bool PadFiveKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_KP_5);
    if (PadFiveKeyIsPressed && !PadFiveKeyWasPressed) {
        self->_fdf->getColorManager()->setColorSet(4);
        needsRedraw = true;
    }
    PadFiveKeyWasPressed = PadFiveKeyIsPressed;

    bool PadSixKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_KP_6);
    if (PadSixKeyIsPressed && !PadSixKeyWasPressed) {
        self->_fdf->getColorManager()->setColorSet(5);
        needsRedraw = true;
    }
    PadSixKeyWasPressed = PadSixKeyIsPressed;

    // EFFECTS
    bool oneKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_1);
    if (oneKeyIsPressed && !oneKeyWasPressed) {
        self->setAutoRotate(!self->getAutoRotate());
        needsRedraw = true;
    }
    oneKeyWasPressed = oneKeyIsPressed;

    bool twoKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_2);
    if (twoKeyIsPressed && !twoKeyWasPressed) {
        self->_fdf->getVFX()->setJitterStatus(!self->_fdf->getVFX()->getJitterStatus());
        needsRedraw = true;
    }
    twoKeyWasPressed = twoKeyIsPressed;

    bool threeKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_3);
    if (threeKeyIsPressed && !threeKeyWasPressed) {
        self->_fdf->getVFX()->setWaveStatus(!self->_fdf->getVFX()->getWaveStatus());
        needsRedraw = true;
    }
    threeKeyWasPressed = threeKeyIsPressed;

    bool fourKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_4);
    if (fourKeyIsPressed && !fourKeyWasPressed) {
        self->_fdf->getVFX()->setGlitchStatus(!self->_fdf->getVFX()->getGlitchStatus());
        needsRedraw = true;
    }
    fourKeyWasPressed = fourKeyIsPressed;

    bool fiveKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_5);
    if (fiveKeyIsPressed && !fiveKeyWasPressed) {
        self->_fdf->getVFX()->setPulseWaveStatus(!self->_fdf->getVFX()->getPulseWaveStatus());
        needsRedraw = true;
    }
    fiveKeyWasPressed = fiveKeyIsPressed;

    bool sixKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_6);
    if (sixKeyIsPressed && !sixKeyWasPressed) {
        self->_fdf->getVFX()->setVortexDistortionStatus(!self->_fdf->getVFX()->getVortexDistortionStatus());
        needsRedraw = true;
    }
    sixKeyWasPressed = sixKeyIsPressed;

    if (self->getAutoRotate()) {
        self->_fdf->rotateZ(0.02f);
        needsRedraw = true;
    }

     if (needsRedraw || (self->_fdf->getVFX()->getJitterIntensity() > 0 && frameCount % 2 == 0)) {
        self->clearImage(self->_img);
        self->_fdf->draw();
    }

    frameCount++;
}

void MLXHandler::scrollHook(double xdelta, double ydelta, void *param)
{
    MLXHandler *self = static_cast<MLXHandler *>(param);
    static int frameCount = 0;
    bool needsRedraw = false;
    (void)xdelta;
    
    // Get current mouse position
    int32_t mouseX, mouseY;
    mlx_get_mouse_pos(self->_mlx, &mouseX, &mouseY);
    
    if (ydelta > 0) {
        self->_fdf->zoom(1.1, mouseX, mouseY);
        needsRedraw = true;
    }
    else if (ydelta < 0) {
        self->_fdf->zoom(0.9, mouseX, mouseY);
        needsRedraw = true;
    }
    
    if (needsRedraw) {
        self->clearImage(self->_img);
        self->_fdf->draw();
    }
    frameCount++;
}

void MLXHandler::perspectiveHooks(void *param){
	MLXHandler *self = static_cast<MLXHandler *>(param);

	if (mlx_is_key_down(self->_mlx, MLX_KEY_F1)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(1);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_F2)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(2);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_F3)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(3);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_F4)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(4);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_F5)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(5);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_F6)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(6);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_F7)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(7);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_F8)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(8);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_F9)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(9);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

    if (mlx_is_key_down(self->_mlx, MLX_KEY_F10)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(10);
        self->_fdf->centerCamera();
		self->_fdf->draw();
	}

    if (mlx_is_key_down(self->_mlx, MLX_KEY_F11)){
        self->clearImage(self->_img);
        self->_fdf->getProjector()->setType(11);
        self->_fdf->centerCamera();
        self->_fdf->draw();
    }

    if (mlx_is_key_down(self->_mlx, MLX_KEY_F12)){
        self->clearImage(self->_img);
        self->_fdf->getProjector()->setType(12);
        self->_fdf->centerCamera();
        self->_fdf->draw();
    }
}