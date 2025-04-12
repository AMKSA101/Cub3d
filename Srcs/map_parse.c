/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:33:10 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 10:06:20 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	parse_map(char **map, t_scene *scene)
{
	int i;

	if (!map)
		return(print_error("Map array is NULL", __FILE__, __LINE__), -1);
	i = 0;
	while (map[i])
	{
		if (check_map_line(map[i]) == -1)
			return (-1);
		i++;
	}
	scene->map_height = i;
	if (check_map_valid(map, scene) == -1)
		return (-1);
	scene->map = map;
	return (0);
}

int check_map_line(char *line)
{
	int i;

	if (!line)
		return (print_error("Map line is NULL", __FILE__, __LINE__), -1);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (print_error("Invalid character in map", __FILE__, __LINE__), -1);
		i++;
	}
	return (0);
}

int check_line(char *line)
{
	int i;

	if (!line)
		return (-1);
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (-1);
		i++;
	}
	return (0);
}

int	check_borders(char **map, t_scene *scene)
{
	size_t	i;
	size_t	j;
	size_t map_width;

	if (check_line(map[0]) == -1)
		return (-1);
	if (check_line(map[scene->map_height - 1]) == -1)
		return (-1);

	i = 0;
	while (i < scene->map_height)
	{
		map_width = ft_strlen(map[i]);
		if (map[i][0] != '1' || map[i][map_width - 1] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int check_map_valid(char **map, t_scene *scene)
{
	size_t i;
	size_t player_count;

	if (!map)
		return (print_error("Map array is NULL", __FILE__, __LINE__), -1);
	player_count = 0;
	i = 0;
	if (check_borders(map, scene) == -1)
		return (print_error("Invalid map border", __FILE__, __LINE__), -1);
	while (map[i])
	{
		if (process_map_line(map, i, &player_count, scene) == -1)
			return (-1);
		i++;
	}
	if (player_count != 1)
		return(print_error("Wrong player count", __FILE__, __LINE__), -1);
	return (0);
}
