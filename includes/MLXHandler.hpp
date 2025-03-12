/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:42:55 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 11:49:31 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXHANDLER_HPP
# define MLXHANDLER_HPP

# include <iostream>
# include <stdexcept>
# include  "../libs/mlx42/include/MLX42/MLX42.h"

class MLXHandler{
	private:
    	MLXHandler();
		
		int	_width;
		int	_height;
		const char *_title;
		
		mlx_t *_mlx;
		mlx_image_t *_img;

	public:
		//Constructors and destructor
		MLXHandler(int width, int height, const char* title);
		MLXHandler(const MLXHandler &other);
		~MLXHandler();

		//Operator overload
		MLXHandler &operator=(const MLXHandler &other);

		//Getters
		int &getHeight();
		int &getWidth();
		mlx_image_t *getImage() const;
		mlx_t *getMLX() const;

		//Methods
		void render() const;
		void handleEvents();
};

#endif