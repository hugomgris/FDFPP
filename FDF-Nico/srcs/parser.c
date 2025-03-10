/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:15:12 by nponchon          #+#    #+#             */
/*   Updated: 2025/03/06 14:13:10 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

int	check_extension(char *file)
{
	int		i;
	int		j;
	char	*extension;

	i = 0;
	j = 0;
	extension = ".fdf";
	while (file[i])
	{
		if (file[i] == extension[j])
		{
			while (file[i + j] == extension[j])
			{
				if (file[i + j + 1] == '\0'
					&& extension[j + 1] == '\0')
					return (1);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

void	get_content(int fd, t_map *env)
{
	int		i;
	char	*line;

	i = 0;
	env->grid2d = (char **)malloc(sizeof(char *) * (env->rows + 1));
	if (!env->grid2d)
		print_error(ENOMEM);
	env->grid2d[env->rows] = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		env->grid2d[i++] = ft_strdup(line);
		free(line);
	}
	if (env->grid2d[0] == NULL)
	{
		free_array((void **)env->grid2d);
		print_error(EBADF);
	}
}

int	count_rows(int fd)
{
	int		count;
	char	*line;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count++;
		free(line);
	}
	return (count);
}

int	check_string(char *file, t_map *env)
{
	if (ft_strlen(file) > 9 || !ft_isdigit_str(file))
		return (false);
	env->grid2d = build_map_from_string(file);
	env->rows = 12;
	return (true);
}

void	check_input(char *file, t_map *env)
{
	int		fd;

	if (!check_extension(file))
	{
		if (!check_string(file, env))
			print_error(EINVAL);
		return ;
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error(EBADF);
	env->rows = count_rows(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error(EBADF);
	get_content(fd, env);
	close(fd);
}
