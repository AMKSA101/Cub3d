/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:38:31 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 10:41:42 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	allocate_components(char ***texture, char ***color, char ***map, int size, int map_start)
{
	if (ft_alloc(texture, 4) == -1)
		return (-1);
	if (ft_alloc(color, 2) == -1)
	{
		double_free(*texture);
		return (-1);
	}
	if (ft_alloc(map, size - map_start) == -1)
	{
		double_free(*texture);
		double_free(*color);
		return (-1);
	}
	return (0);
}

int	find_map_start(char **content, int size)
{
	int		i;
	int		map_start;

	i = 0;
	map_start = -1;
	while (i < size)
	{
		if (content[i][0] == '1' || content[i][0] == '0')
		{
			map_start = i;
			break;
		}
		i++;
	}
	if (map_start == -1)
		return (print_error("No valid map found", __FILE__, __LINE__), -1);
	return (map_start);
}

int	extract_textures_and_colors(char **content, int map_start, char **texture, char **color)
{
	int		i;
	int		texture_index;
	int		color_index;

	texture_index = 0;
	color_index = 0;
	i = 0;
	while (i < map_start)
	{
		if (texture_index < 4 && (ft_strncmp(content[i], "NO", 2) == 0 || 
			ft_strncmp(content[i], "SO", 2) == 0 || 
			ft_strncmp(content[i], "WE", 2) == 0 || 
			ft_strncmp(content[i], "EA", 2) == 0))
			texture[texture_index++] = ft_strdup(content[i]);
			
		else if (color_index < 2 && (ft_strncmp(content[i], "F", 1) == 0 || 
			ft_strncmp(content[i], "C", 1) == 0))
			color[color_index++] = ft_strdup(content[i]);
			
		else
			return (-1);
		i++;
	}
	return (0);
}

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
