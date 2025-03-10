/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:07:10 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/06 14:23:43 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

/*	alpha = 0.78 radians or 45 degrees	*/

void	init_env(t_map *env)
{
	env->rows = 0;
	env->cols = 0;
	env->max = 0;
	env->min = 0;
	env->offset_x = WINDOW_WIDTH / 2;
	env->offset_y = WINDOW_HEIGHT / 4;
	env->interval = 5;
	env->elevation = 0;
	env->alpha = 0.78;
	env->beta = 2;
	env->zoom = 1;
	env->map_colour = -1;
	env->flat_mode = -1;
}

int	main(int ac, char **av)
{
	t_map	env;

	if (ac == 2)
	{
		init_env(&env);
		check_input(av[1], &env);
		set_matrix(&env);
		//free_array((void **)env.grid2d);
		if (!init_window(&env))
		{
			//free_fgrid(&env);
			//free_matrix(&env);
			return (EXIT_FAILURE);
		}
		//free_fgrid(&env);
		//free_matrix(&env);
	}
	else
		print_error(EINVAL);
	return (EXIT_SUCCESS);
}
