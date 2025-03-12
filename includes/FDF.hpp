/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:06:36 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 12:38:50 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_HPP
# define FDF_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include <climits>
# include "MLXHandler.hpp"
# include "projections/OrthographicProjection.hpp"
# include "projections/IsometricProjection.hpp"
# include "projections/PerspectiveProjection.hpp"

class FDF{
	private:
		std::vector<std::vector<int>> _matrix;
		int _matrixWidth;
		int _matrixHeight;
		
		int _horizontalOffset;
		int _verticalOffset;
		int _spacing;
		
		IProjection *_projection;
		MLXHandler _MLXHandler;
	
	public:
		//Constructor and destructor
		FDF(std::vector<std::string> &map, IProjection *projection, MLXHandler &MLXHandler);
		~FDF();

		//Methods
		int getZ(int x, int y) const;
		void calculateOffset();
		void draw();
		void drawPoints();
		void drawLines();
		void drawLine(std::pair<int, int> start, std::pair<int, int> end, int color);

		//Getters
		std::vector<std::vector<int>> &getMatrix();

		//Debug methods
		void printMatrix() const;
};

#endif