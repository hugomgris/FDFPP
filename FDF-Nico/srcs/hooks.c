/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:59:54 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/11 11:59:56 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

void	ft_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->map->elevation += 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		if (fdf->map->elevation >= 0.05)
			fdf->map->elevation -= 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->map->offset_y -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->map->offset_y += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->map->offset_x -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->map->offset_x += 5;
}

void	ft_hook_rotations(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->map->zoom += 0.075;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		if (fdf->map->zoom >= 0)
			fdf->map->zoom -= 0.075;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		fdf->map->alpha += 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
		fdf->map->alpha -= 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
		fdf->map->alpha = 0.78;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
		fdf->map->alpha = 1.57;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_T))
		fdf->map->alpha = 0.866;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_U))
		fdf->map->flat_mode = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
		fdf->map->flat_mode = -1;
}
