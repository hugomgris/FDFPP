/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:19:41 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/04/02 15:13:34 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_HPP
# define UI_HPP

#include <vector>

# include "MLXHandler.hpp"
# include "HeightMap.hpp"

class UI {
	private:
		HeightMap *_heightMap;
		MLXHandler *_MLXHandler;
		std::vector<mlx_image_t*> _textImages;
		int _uiWidth;
		int _uiHeight;

		int _interlineSpacing;

		std::vector<std::string> _controls;
		std::vector<std::string> _controls2;
		int _controlsOffset;

		std::string _nPoints;
		std::string _nEdges;
		

	public:
		// Constructor and destructor
		UI(HeightMap *heightMap, MLXHandler *mlxhandler, int uiWidth, int uiHeight);
		~UI();

		// Getters
		mlx_image_t *getUI() const;

		// Methods
		void fillBackground();
		void ColorText(mlx_image_t *img, uint8_t targetR, uint8_t targetG, uint8_t targetB);
		void outputControls();
		void clearTexts();
};

#endif
