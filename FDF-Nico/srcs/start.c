/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:15:12 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 10:15:21 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

void	drawing_algo(t_fdf *fdf, t_fpoint start, t_fpoint end)
{
	t_delta	delta;
	int		i;

	delta.dx = end.x - start.x;
	delta.dy = end.y - start.y;
	if (fabs(delta.dx) >= fabs(delta.dy))
		delta.step = fabs(delta.dx);
	else
		delta.step = fabs(delta.dy);
	delta.dx = delta.dx / delta.step;
	delta.dy = delta.dy / delta.step;
	delta.x = start.x;
	delta.y = start.y;
	i = 0;
	while (i++ <= delta.step)
	{
		if (delta.x + fdf->map->offset_x > 0 \
			&& delta.x + fdf->map->offset_x < WINDOW_WIDTH \
			&& delta.y + fdf->map->offset_y > 0 \
			&& delta.y + fdf->map->offset_y < WINDOW_HEIGHT)
			mlx_put_pixel(fdf->img, delta.x + fdf->map->offset_x,
				delta.y + fdf->map->offset_y, start.colour);
		delta.x += delta.dx;
		delta.y += delta.dy;
	}
}

void	draw_line(t_fdf *fdf, int x, int y)
{
	if (x == fdf->map->rows && y == fdf->map->cols)
		return ;
	if (x + 1 < fdf->map->rows)
	{
		drawing_algo(fdf, fdf->map->fgrid[x][y], fdf->map->fgrid[x + 1][y]);
	}
	if (y + 1 < fdf->map->cols)
	{
		drawing_algo(fdf, fdf->map->fgrid[x][y], fdf->map->fgrid[x][y + 1]);
	}
}

void	draw_image(void *param)
{
	t_fdf	*fdf;
	int		i;
	int		j;

	fdf = param;
	reset_image(fdf);
	if (fdf->map->flat_mode == -1)
		set_projection(fdf->map);
	else
		set_2dmode(fdf->map);
	i = -1;
	while (++i < fdf->map->rows)
	{
		j = -1;
		while (++j < fdf->map->cols)
		{
			draw_line(fdf, i, j);
		}
	}
}

/*
void	display_menu(t_fdf *fdf)
{
	int		x;
	int		y;

	x = 20;
	y = 20;
	mlx_put_string(fdf->mlx, "USE ARROWS TO MOVE", x, y);
	mlx_put_string(fdf->mlx, "USE W & S TO CHANGE ELEVATION", x, y + 20);
	mlx_put_string(fdf->mlx, "USE _ & + TO ZOOM IN AND OUT", x, y + 40);
	mlx_put_string(fdf->mlx, "USE 1 & 2 TO ROTATE", x, y + 60);
	mlx_put_string(fdf->mlx, "USE R TO RESET", x, y + 80);
	mlx_put_string(fdf->mlx, "USE Y FOR PARALLEL PROJECTION", x, y + 100);
	mlx_put_string(fdf->mlx, "USE T FOR REAL ISOMETRIC PROJECTION", x, y + 120);
	mlx_put_string(fdf->mlx, "USE U TO ACTIVATE 2D PROJECTION", x, y + 140);
	mlx_put_string(fdf->mlx, "USE T TO DEACTIVATE 2D PROJECTION", x, y + 160);
}*/

int	init_window(t_map *env)
{
	t_fdf		fdf;

	fdf.map = env;
	fdf.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF@nponchon", true);
	fdf.img = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!fdf.mlx || !fdf.img)
		return (EXIT_FAILURE);
	set_projection(fdf.map);
	draw_image(&fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	mlx_loop_hook(fdf.mlx, ft_hook_rotations, &fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop_hook(fdf.mlx, draw_image, &fdf);
	mlx_loop(fdf.mlx);
	mlx_delete_image(fdf.mlx, fdf.img);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
