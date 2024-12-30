/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:42:18 by abamksa           #+#    #+#             */
/*   Updated: 2024/12/30 11:20:27 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void print_error(char *error, char *file, char *line)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" at line ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(RESET, 2);
	exit(1);
}

void free_scene(t_scene *scene)
{
	if (scene->north)
		free(scene->north);
	if (scene->south)
		free(scene->south);
	if (scene->west)
		free(scene->west);
	if (scene->east)
		free(scene->east);
	if (scene->map)
	{
		size_t i = -1;
		while (++i < scene->map_height)
			free(scene->map[i]);
		free(scene->map);
	}
}
