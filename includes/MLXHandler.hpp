/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:42:55 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/17 14:18:57 by hmunoz-g         ###   ########.fr       */
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
		const char *_title;
		
		mlx_t *_mlx;
		mlx_image_t *_img;

		FDF *_fdf;

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
		mlx_image_t *getImage() const;
		mlx_t *getMLX() const;

		void setFDF(FDF *fdf);

		//Methods
		void render() const;
		void handleEvents();
		void clearImage(mlx_image_t *img);
		void cleanup();

		static void basicHooks(void *param);
		static void perspectiveHooks(void *param);
};

#endif