/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:19:41 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/28 16:03:37 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_HPP
# define UI_HPP

#include <vector>

# include "MLXHandler.hpp"

class UI {
	private:
		MLXHandler *_MLXHandler;
		std::vector<mlx_image_t*> _textImages;
		int _uiWidth;
		int _uiHeight;

	public:
		// Constructor and destructor
		UI(MLXHandler *mlxhandler, int uiWidth, int uiHeight);
		~UI();

		// Getters
		mlx_image_t *getUI() const;

		// Methods
		void fillBackground();
		void RedText(mlx_image_t *img);
		void outputControls();
		void clearTexts();
};

#endif
