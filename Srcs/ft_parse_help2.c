/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_help2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:00:31 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/15 15:59:04 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	copy_map_data(char **content, int map_start, int size, char **map)
{
	int	i;

	i = 0;
	while (i < (size - map_start))
	{
		map[i] = ft_strdup(content[map_start + i]);
		i++;
	}
	return (0);
}

int	calculate_map_width(t_scene *scene)
{
	size_t	i;
	size_t	current_width;

	i = 0;
	scene->map_width = ft_strlen(scene->map[0]);
	while (scene->map[i])
	{
		current_width = ft_strlen(scene->map[i]);
		if (scene->map_width < current_width)
			scene->map_width = current_width;
		i++;
	}
	return (0);
}

void	free_all(t_data *data)
{
	if (data->texture)
	{
		if (data->texture->north)
			mlx_destroy_image(data->mlx->mlx_ptr, data->texture->north);
		if (data->texture->south)
			mlx_destroy_image(data->mlx->mlx_ptr, data->texture->south);
		if (data->texture->west)
			mlx_destroy_image(data->mlx->mlx_ptr, data->texture->west);
		if (data->texture->east)
			mlx_destroy_image(data->mlx->mlx_ptr, data->texture->east);
		free(data->texture);
	}
	free_scene(data->scene);
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_zero_boundaries(char **map, size_t i, size_t j, size_t map_width)
{
	if (j == 0 || j == map_width - 1)
		return (0);
	if ((j > 0 && map[i][j - 1] == ' ')
		|| (j < map_width - 1 && map[i][j + 1] == ' '))
		return (0);
	return (1);
}
