/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:06:36 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/14 18:01:30 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_HPP
# define FDF_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include <climits>
# include "MLXHandler.hpp"
# include "VFX.hpp"
# include "projections/Projector.hpp"


class FDF{
	private:
		std::vector<std::vector<int>> _matrix;
		int _matrixWidth;
		int _matrixHeight;
		
		int _minHeight;
		int _maxHeight;
		
		int _horizontalOffset;
		int _verticalOffset;
		int _spacing;
		double _zFactor;

		double _zoomLevel;
		int _cameraX;
		int _cameraY;

		Projector *_projector;
		MLXHandler _MLXHandler;
		VFX *_vfx;	
	
	public:
		//Constructor and destructor
		FDF(std::vector<std::string> &map, Projector *projector, MLXHandler &MLXHandler, VFX *vfx);
		~FDF();

		//Methods
		int getZ(int x, int y) const;
		void calculateOffset();
		void calculateInitialScale();
		void draw();
		void drawPoints();
		void drawLines();
		void drawLine(std::pair<int, int> start, std::pair<int, int> end, int z1, int z2);
		void drawLineSafe(std::pair<int, int> start, std::pair<int, int> end, int color);
		void zoom(double factor, int mouseX, int mouseY);
		void pan(int dx, int dy);
		void centerCamera();

		//Point color calculation
		void calculateHeightExtremes();
		float normalizeHeight(int z) const;
		int getColor(int z) const;

		//Line color calculation
		int interpolateColor(int color1, int color2, float t);
		int getColorFromHeight(int z);

		//Getters & setters
		std::vector<std::vector<int>> &getMatrix();
		Projector *getProjector();
		VFX *getVFX();
		double getZFactor();

		void setZFactor(double increase, int mode);

		//Debug methods
		void printMatrix() const;
};

#endif