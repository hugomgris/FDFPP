/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:07:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 15:30:08 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

void	count_columns(t_map *env)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (env->grid2d[0][i])
	{
		if (ft_isalnum(env->grid2d[0][i])
		&& (env->grid2d[0][i + 1] == ' ' || env->grid2d[0][i + 1] == '\n'
		|| env->grid2d[0][i + 1] == '\0'))
			nb++;
		i++;
	}
	i = 1;
	env->cols = nb;
}

void	get_columns(t_map *env, int i)
{
	t_point	*point;
	char	**line_tab;
	int		j;

	line_tab = ft_split(env->grid2d[i], ' ');
	j = -1;
	while (++j < env->cols)
	{
		env->max = get_max(env->max, ft_atoi(line_tab[j]));
		env->min = get_min(env->min, ft_atoi(line_tab[j]));
		point = &(env->grid3d[i][j]);
		point->x = j;
		point->y = i;
		point->colour = 0x00bca1FF;
		point->z = ft_atoi(line_tab[j]);
		if (ft_strchr(line_tab[j], ',') != NULL)
		{
			env->map_colour = 1;
			env->grid3d[i][j].colour = \
				ft_atoi_base(ft_strchr(line_tab[j], ',') + 3, 16);
		}
	}
	free_array((void **)line_tab);
}

void	malloc_grid(t_map *env)
{
	int	i;

	env->grid3d = malloc(sizeof(t_point *) * env->rows);
	env->fgrid = malloc(sizeof(t_fpoint *) * env->rows);
	if (!(env->grid3d) || !(env->fgrid))
	{
		free_matrix(env);
		print_error(ENOMEM);
	}
	i = -1;
	while (++i < env->rows)
	{
		env->grid3d[i] = malloc(sizeof(t_point) * env->cols);
		env->fgrid[i] = malloc(sizeof(t_fpoint) * env->cols);
		if (!(env->grid3d) || !(env->fgrid))
		{
			free_matrix(env);
			print_error(ENOMEM);
		}
	}
}

void	set_projection(t_map *env)
{
	int		i;
	int		j;

	i = -1;
	while (++i < env->rows)
	{
		j = -1;
		while (++j < env->cols)
		{
			env->fgrid[i][j].x = (int)(env->grid3d[i][j].x * env->interval)
				* sinf(env->alpha) + ((int)env->grid3d[i][j].z
					* sinf(env->alpha - PI / 2) * env->elevation);
			env->fgrid[i][j].y = (int)(env->grid3d[i][j].y * env->interval)
				* cosf(env->alpha) + ((int)-env->grid3d[i][j].z
					* cosf(env->alpha - PI / 2) * env->elevation);
			env->fgrid[i][j].x = (env->fgrid[i][j].x / env->beta)
				- (env->fgrid[i][j].y / env->beta);
			env->fgrid[i][j].y = (env->fgrid[i][j].x / env->beta)
				+ (env->fgrid[i][j].y / env->beta);
			env->fgrid[i][j].x *= env->zoom;
			env->fgrid[i][j].y *= env->zoom;
			set_pointcolour(env, i, j);
		}
	}
}

void	set_matrix(t_map *env)
{
	int		i;

	count_columns(env);
	malloc_grid(env);
	i = -1;
	while (env->grid2d[++i] != NULL)
		get_columns(env, i);
	set_interval(env);
	if (env->max > 10)
		env->elevation = 0.00;
	else
		env->elevation = 20;
}
