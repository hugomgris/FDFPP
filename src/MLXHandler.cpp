/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:41:26 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/11 14:56:15 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MLXHandler.hpp"

//Constructors and destructor
MLXHandler::MLXHandler(int width, int height, const char *title): _width(width), _height(height), _title(title){
	this->_mlx = mlx_init(this->_width, this->_height, this->_title, true);

	if (!this->_mlx)
		throw std::runtime_error("MLX failed to initialize");
	
	this->_img = mlx_new_image(this->_mlx, this->_width, this->_height);
	if (!this->_img){
		throw std::runtime_error("Failed to create image buffer");
	}

	mlx_image_to_window(this->_mlx, this->_img, 0, 0);
	//mlx_put_pixel(this->_img, 100, 100, 0x22222200);
}

MLXHandler::MLXHandler(const MLXHandler &other): _title(other._title){
	*this = other;
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

//Methods
void MLXHandler::render() const{
	mlx_loop(this->_mlx);
}

void MLXHandler::handleEvents(){
	std::cout << "cucufu\n";
}