/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:06:36 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/11 17:25:25 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_HPP
# define FDF_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include "MLXHandler.hpp"
# include "projections/OrthographicProjection.hpp"
# include "projections/IsometricProjection.hpp"
# include "projections/PerspectiveProjection.hpp"

class FDF{
	private:
		std::vector<std::vector<int>> _matrix;
		int _width;
		int _height;
		
		IProjection *_projection;
		MLXHandler _MLXHandler;
	
	public:
		//Constructor and destructor
		FDF(std::vector<std::string> &map, IProjection *projection, MLXHandler &MLXHandler);
		~FDF();

		//Methods
		int getZ(int x, int y) const;

		//Getters
		std::vector<std::vector<int>> &getMatrix();

		//Debug methods
		void printMatrix() const;
		void drawPoints() const;
};

#endif