/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:41:26 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/14 10:02:02 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MLXHandler.hpp"
#include "../includes/FDF.hpp"

//Constructors and destructor
MLXHandler::MLXHandler(int width, int height, const char *title): _width(width), _height(height), _title(title){
	this->_mlx = mlx_init(this->_width, this->_height, this->_title, true);

	if (!this->_mlx)
		throw std::runtime_error("MLX failed to initialize");
	
	if (!this->_mlx->window) {
	throw std::runtime_error("MLX initialized but window is NULL! Check OpenGL support.");
}
	
	this->_img = mlx_new_image(this->_mlx, this->_width, this->_height);
	if (!this->_img){
		throw std::runtime_error("Failed to create image buffer");
	}

	mlx_image_to_window(this->_mlx, this->_img, 0, 0);
}

MLXHandler::MLXHandler(const MLXHandler &other): _title(other._title){
	*this = other;
}

MLXHandler::~MLXHandler(){
    /*if (this->_mlx) {
        if (this->_img) {
            mlx_delete_image(this->_mlx, this->_img);
            this->_img = nullptr;
        }
        mlx_terminate(this->_mlx);
        this->_mlx = nullptr;
    }*/
}

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

mlx_image_t *MLXHandler::getImage() const{
	return (_img);
}

mlx_t *MLXHandler::getMLX() const{
	return (_mlx);
}

void MLXHandler::setFDF(FDF *fdf){
	_fdf = fdf;
}

//Methods
void MLXHandler::render() const{
	mlx_loop(this->_mlx);
}

void MLXHandler::handleEvents(){
	mlx_loop_hook(_mlx, basicHooks, this);
	mlx_loop_hook(_mlx, perspectiveHooks, this);
}

void MLXHandler::clearImage(mlx_image_t *img){
    (void)img;
	for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            mlx_put_pixel(_img, x, y, 0x000000);
        }
    }
}

void MLXHandler::basicHooks(void *param){
	MLXHandler *self = static_cast<MLXHandler *>(param);
	static int frameCount = 0;

	if (mlx_is_key_down(self->_mlx, MLX_KEY_ESCAPE)) 
		mlx_close_window(self->_mlx);

	else if (mlx_is_key_down(self->_mlx, MLX_KEY_UP)){
		self->clearImage(self->_img);
		self->_fdf->setZFactor(0.1, 1);
		self->_fdf->draw();
	}

	else if (mlx_is_key_down(self->_mlx, MLX_KEY_DOWN)){
		self->clearImage(self->_img);
		self->_fdf->setZFactor(0.1, -1);
		self->_fdf->draw();
	}

	else if (mlx_is_key_down(self->_mlx, MLX_KEY_KP_SUBTRACT)) {
        self->clearImage(self->_img);
		self->_fdf->zoom(0.9);
		self->_fdf->draw();
	}

	else if (mlx_is_key_down(self->_mlx, MLX_KEY_KP_ADD)) {
        self->clearImage(self->_img);
		self->_fdf->zoom(1.1);
		self->_fdf->draw();
	}

	else if (mlx_is_key_down(self->_mlx, MLX_KEY_W)) {
        self->clearImage(self->_img);
		self->_fdf->pan(10, 0);
		self->_fdf->draw();
	}

	else if (mlx_is_key_down(self->_mlx, MLX_KEY_S)) {
        self->clearImage(self->_img);
		self->_fdf->pan(-10, 0);
		self->_fdf->draw();
	}

	else if (mlx_is_key_down(self->_mlx, MLX_KEY_A)) {
        self->clearImage(self->_img);
		self->_fdf->pan(0, 10);
		self->_fdf->draw();
	}

	else if (mlx_is_key_down(self->_mlx, MLX_KEY_D)) {
        self->clearImage(self->_img);
		self->_fdf->pan(0, -10);
		self->_fdf->draw();
	}

	//This needs to be in renderHooks or something like that
	else if (mlx_is_key_down(self->_mlx, MLX_KEY_J)){
		if (self->_fdf->getVFX()->getJitterIntensity())
			self->_fdf->getVFX()->setJitterIntensity(.0f);
		else
			self->_fdf->getVFX()->setJitterIntensity(1.5f);
	}

	if (frameCount % 2 == 0){
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