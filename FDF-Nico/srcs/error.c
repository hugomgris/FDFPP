/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:54:24 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 18:54:26 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

void	free_array(void **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}

void	free_matrix(t_map *env)
{
	int	i;

	i = -1;
	while (++i < env->rows)
		free(env->grid3d[i]);
	free(env->grid3d);
	env->grid3d = NULL;
}

void	free_fgrid(t_map *env)
{
	int	i;

	i = -1;
	while (++i < env->rows)
		free(env->fgrid[i]);
	free(env->fgrid);
	env->fgrid = NULL;
}

void	print_error(int err)
{
	errno = err;
	perror("Error");
	exit(EXIT_FAILURE);
}
