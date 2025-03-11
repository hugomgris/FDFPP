/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:06:16 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/11 17:25:24 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.hpp"

//Constructor and destructor
FDF::FDF(std::vector<std::string> &map, IProjection *projection, MLXHandler &MLXHandler): 
	_projection(projection), _MLXHandler(MLXHandler){
		for (const std::string & line : map){
			std::istringstream iss(line);
			std::vector<int> row;

			int value;
			while (iss >> value){
				row.push_back(value);
			}
			_matrix.push_back(row);
		}

		_height = _matrix.size();
		_width = _matrix[0].size();
}

FDF::~FDF(){}

//Getters
std::vector<std::vector<int>> &FDF::getMatrix(){
	return (_matrix);
}

//Methods
int FDF::getZ(int x, int y) const{
	if (x < 0 || x >= _height|| y < 0 || y >= _width)
		return (0);
	return (_matrix[x][y]);
}

void FDF::drawPoints() const {
	int spacing = 20;
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			//int z = getZ(x, y);
			int drawX = x * spacing;
			int drawY = y * spacing;

			mlx_put_pixel(_MLXHandler.getImage(), drawX, drawY, 0xFFFFFF); // White color
		}
	}
	mlx_image_to_window(_MLXHandler.getMLX(), _MLXHandler.getImage(), 0, 0);
}

//Debug methods
void FDF::printMatrix() const{
	for (int x = 0; x < _height; x++){
		for (int y = 0; y < _width; y++){
			std::cout << getZ(x, y) << " ";
		}
		std::cout << std::endl;
	}
}