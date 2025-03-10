/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:11:32 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/06 14:05:21 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../../Map_Builder/map_builder_wrapper.h"

# define WINDOW_WIDTH 	1920
# define WINDOW_HEIGHT 	1080

# define PI				3.14

//	Colour gradient from red to blue

# define COLOUR_ONE 	0xB8890Fff//0xab9a00ff
# define COLOUR_TWO 	0x80960dff
# define COLOUR_THREE 	0x4b902dff
# define COLOUR_FOUR 	0x008846ff
# define COLOUR_FIVE 	0x00765dff
# define COLOUR_SIX 	0x006563ff
# define COLOUR_SEVEN 	0x005563ff
# define COLOUR_EIGHT 	0x004463ff
# define COLOUR_NINE 	0x003266ff
# define COLOUR_TEN 	0x02007cff

//		POINT STRUCTURE (X = COL, Y = ROW, Z = ALTITUDE)

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		colour;
}	t_point;

typedef struct s_fpoint
{
	int	x;
	int	y;
	int	z;
	int	colour;
}	t_fpoint;

typedef struct s_delta
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	step;
}	t_delta;

typedef struct s_map
{
	int			rows;
	int			cols;
	int			max;
	int			min;
	int			offset_x;
	int			offset_y;
	int			map_colour;
	int			flat_mode;
	double		interval;
	double		elevation;
	double		alpha;
	double		beta;
	float		zoom;
	char		**grid2d;
	t_point		**grid3d;
	t_fpoint	**fgrid;
	mlx_image_t	*img;
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*img;
}	t_fdf;

//		CHECK AND PARSE INPUT

void		check_input(char *file, t_map *env);
void		get_content(int fd, t_map *env);
int			check_extension(char *file);
int			count_rows(int fd);
int			count_rows(int fd);

//		SET MATRIX

void		init_env(t_map *env);
void		get_matrix(t_map *env);
void		set_matrix(t_map *env);
void		count_columns(t_map *env);
void		get_columns(t_map *env, int i);
void		set_interval(t_map *env);
int			get_max(int a, int b);
int			get_min(int a, int b);
void		set_pointcolour(t_map *env, int i, int j);

//		WINDOW AND DRAWING

int			init_window(t_map *env);
void		ft_hook(void *param);
void		ft_hook_rotations(void *param);
void		set_projection(t_map *env);
void		set_2dmode(t_map *env);
void		drawing_algo(t_fdf *fdf, t_fpoint start, t_fpoint end);
void		draw_image(void *param);
void		draw_line(t_fdf *fdf, int x, int y);
void		reset_image(t_fdf *fdf);
double		get_percentage(int start, int end, int current);
int			set_colour(double percentage);
void		display_menu(t_fdf *fdf);

//		ERROR, FREE & DEBUG

void		print_error(int err);
void		free_array(void **array);
void		free_matrix(t_map *env);
void		free_fgrid(t_map *env);
void		print_matrix(t_map *env);

#endif
