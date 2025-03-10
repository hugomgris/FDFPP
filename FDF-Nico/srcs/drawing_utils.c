/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:25:16 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/09 20:25:18 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

void	set_pointcolour(t_map *env, int i, int j)
{
	float	percentage;

	percentage = 0;
	if (env->map_colour == -1)
	{
		percentage = get_percentage(env->max, env->min, env->grid3d[i][j].z);
		env->fgrid[i][j].colour = set_colour(percentage);
	}
	else
		env->fgrid[i][j].colour = env->grid3d[i][j].colour;
}

void	reset_image(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while ((uint32_t)++i < fdf->img->width)
	{
		j = -1;
		while ((uint32_t)++j < fdf->img->height)
		{
			mlx_put_pixel(fdf->img, i, j, 0x22222200);
		}
	}
}

void	set_2dmode(t_map *env)
{
	int		i;
	int		j;

	i = -1;
	while (++i < env->rows)
	{
		j = -1;
		while (++j < env->cols)
		{
			env->fgrid[i][j].x = (int)env->grid3d[i][j].x * env->interval;
			env->fgrid[i][j].y = (int)env->grid3d[i][j].y * env->interval;
			env->fgrid[i][j].x *= env->zoom;
			env->fgrid[i][j].y *= env->zoom;
			set_pointcolour(env, i, j);
		}
	}
}
