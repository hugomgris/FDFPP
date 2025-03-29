/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:42:55 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/28 15:54:42 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXHANDLER_HPP
# define MLXHANDLER_HPP

# include <iostream>
# include <stdexcept>
# include <cstring> 
# include "../libs/mlx42/include/MLX42/MLX42.h"

class FDF;

class MLXHandler{
	private:
    	MLXHandler();
		
		int	_width;
		int	_height;
		int _uiWidth;
		int _uiHeight;
		const char *_title;
		
		mlx_t *_mlx;
		mlx_image_t *_img;
		mlx_image_t *_ui;
		mlx_image_t *_text1;
		mlx_image_t *_text2;

		FDF *_fdf;
		bool _autoRotate;

	public:
		//Constructors and destructor
		MLXHandler(int width, int height, const char* title);
		MLXHandler(const MLXHandler &other);
		~MLXHandler();

		//Operator overload
		MLXHandler &operator=(const MLXHandler &other);

		//Getters & Setters
		int &getHeight();
		int &getWidth();
		int &getUIHeight();
		int &getUIWidth();
		mlx_image_t *getImage() const;
		mlx_image_t *getUI() const;
		mlx_image_t *getText1() const;
		mlx_image_t *getText2() const;
		mlx_t *getMLX() const;
		FDF *getFDF() const;
		bool &getAutoRotate();

		void setAutoRotate(bool autoRotate);
		void setFDF(FDF *fdf);

		//Methods
		void render() const;
		void handleEvents();
		void clearImage(mlx_image_t *img);
		void cleanup();

		static void basicHooks(void *param);
		static void scrollHook(double xdelta, double ydelta, void *param);
		static void perspectiveHooks(void *param);
};

#endif