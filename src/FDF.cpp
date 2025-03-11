/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:06:16 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/11 16:09:11 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.hpp"

//Constructor and destructor
FDF::FDF(std::vector<std::string> &map, IProjection *projection, MLXHandler &MLXHandler): 
	_projection(projection), _MLXHandler(MLXHandler){
		this->_height = map.size();
		this->_width = map[0].length();

		this->_map.resize(this->_width * this->_height);
		for (size_t y = 0; y < map.size(); y++){
			std::istringstream iss(map[y]);
			for (int x = 0; x < this->_width; x++)
				iss >> this->_map[y * this->_width + x];
		}
	}

FDF::~FDF(){}

//Methods
int FDF::getZ(int x, int y) const{
	if (x < 0 || x >= this->_width || y < 0 || y >= this->_height)
		return (0);
	return this->_map[y * this->_width + x];
}

//Debug methods
void FDF::printMatrix() const{
	for (int y = 0; y < this->_height; y++){
		for (int x = 0; x < this->_width; x++)
			std::cout << getZ(x, y) << " ";
		std::cout << std::endl;
	}
}