/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:41:26 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/28 15:54:38 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MLXHandler.hpp"
#include "../includes/FDF.hpp"

//Constructors and destructor
MLXHandler::MLXHandler(int width, int height, const char *title): _width(width), _height(height), _title(title), _autoRotate(false){
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

void MLXHandler::basicHooks(void *param) {
    MLXHandler *self = static_cast<MLXHandler *>(param);
    static int frameCount = 0;
    static bool jKeyWasPressed = false;
    static bool rKeyWasPressed = false; 
    bool needsRedraw = false;

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
        self->_fdf->rotate(-0.05);
        needsRedraw = true;
    }
    if (mlx_is_key_down(self->_mlx, MLX_KEY_E)) {
        self->_fdf->rotate(0.05);
        needsRedraw = true;
    }

    // Jitter toggle - improved to prevent multiple toggles
    bool jKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_J);
    if (jKeyIsPressed && !jKeyWasPressed) {
        // Only toggle when key is first pressed
        if (self->_fdf->getVFX()->getJitterIntensity() > 0)
            self->_fdf->getVFX()->setJitterIntensity(.0f);
        else
            self->_fdf->getVFX()->setJitterIntensity(1.0f);
        
        needsRedraw = true;
    }
    jKeyWasPressed = jKeyIsPressed;  // Update previous state

    bool rKeyIsPressed = mlx_is_key_down(self->_mlx, MLX_KEY_R);
    if (rKeyIsPressed && !rKeyWasPressed) {
        // Toggle auto-rotate
        self->setAutoRotate(!self->getAutoRotate());
        needsRedraw = true;
    }
    rKeyWasPressed = rKeyIsPressed;

    if (self->getAutoRotate()) {
        self->_fdf->rotate(0.02f);
        needsRedraw = true;
    }

     // Redraw if needed or if jittering is active
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

    if (ydelta > 0) {
        self->_fdf->zoom(1.1, -1, -1);
        needsRedraw = true;
    }
    else if (ydelta < 0) {
        self->_fdf->zoom(0.9, -1, -1);
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

	if (mlx_is_key_down(self->_mlx, MLX_KEY_1)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(1);
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_2)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(2);
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_3)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(3);
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_4)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(4);
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_5)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(5);
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_6)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(6);
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_7)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(7);
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_8)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(8);
		self->_fdf->draw();
	}

	if (mlx_is_key_down(self->_mlx, MLX_KEY_9)){
		self->clearImage(self->_img);
		self->_fdf->getProjector()->setType(9);
		self->_fdf->draw();
	}
}