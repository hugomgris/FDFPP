/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:19:41 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/27 16:45:37 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_HPP
# define UI_HPP

#include <vector>

# include "MLXHandler.hpp"

class UI {
	private:
		mlx_t *_mlx;
		mlx_image_t *_ui;
		int _uiWidth;
		int _uiHeight;
		std::vector<mlx_image_t*> _textImages;

	public:
		// Constructor and destructor
		UI(mlx_t *mlx, mlx_image_t *ui, int uiWidth, int uiHeight);
		~UI();

		// Getters
		mlx_image_t *getUI() const;

		// Methods
		void fillBackground();
		void outputControls();
		void clearTexts();
};

#endif
