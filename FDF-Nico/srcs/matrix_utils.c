/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:07:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 15:30:08 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

void	set_interval(t_map *env)
{
	int	interval_x;
	int	interval_y;

	interval_x = WINDOW_WIDTH / (env->cols * cosf(35));
	interval_y = WINDOW_HEIGHT / (env->rows * sinf(35));
	if (interval_x > interval_y)
		env->interval = -interval_y / 2;
	else
		env->interval = -interval_x / 2;
}

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	set_colour(double percentage)
{
	if (percentage < 0.05)
		return (COLOUR_ONE);
	else if (percentage < 0.2)
		return (COLOUR_TWO);
	else if (percentage < 0.3)
		return (COLOUR_THREE);
	else if (percentage < 0.4)
		return (COLOUR_FOUR);
	else if (percentage < 0.5)
		return (COLOUR_FIVE);
	else if (percentage < 0.6)
		return (COLOUR_SIX);
	else if (percentage < 0.7)
		return (COLOUR_SEVEN);
	else if (percentage < 0.8)
		return (COLOUR_EIGHT);
	else if (percentage < 0.9)
		return (COLOUR_NINE);
	else
		return (COLOUR_TEN);
}

double	get_percentage(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}
