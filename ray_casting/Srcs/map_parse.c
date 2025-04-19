/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:33:10 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/15 16:24:57 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	parse_map(char **map, t_scene *scene)
{
	int	i;

	if (!map)
		return (print_error("Map array is NULL", __FILE__, __LINE__), -1);
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

int	check_map_line(char *line)
{
	int	i;

	if (!line)
		return (print_error("Map line is NULL", __FILE__, __LINE__), -1);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (print_error("Invalid character in map", __FILE__, __LINE__),
				-1);
		i++;
	}
	return (0);
}

int	check_line(char *line)
{
	int	i;

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
	size_t	row_length;

	i = 0;
	while (i < scene->map_height)
	{
		if (i == 0 || i == scene->map_height - 1)
		{
			if (validate_border_row(map, i, scene) == -1)
				return (-1);
		}
		row_length = ft_strlen(map[i]);
		if (row_length > 0)
		{
			if ((map[i][0] != '1' && map[i][0] != ' ')
				|| (map[i][row_length - 1] != '1'
				&& map[i][row_length - 1] != ' '))
				return (-1);
		}
		i++;
	}
	return (0);
}

int	validate_border_row(char **map, size_t i, t_scene *scene)
{
	size_t	j;
	size_t	row_length;

	j = 0;
	row_length = ft_strlen(map[i]);
	while (j < row_length)
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (-1);
		if (map[i][j] == ' ' && i > 0 && i < scene->map_height - 1)
		{
			if (j > 0 && j < row_length - 1
				&& (map[i][j - 1] == '0' || map[i][j + 1] == '0'))
				return (-1);
		}
		j++;
	}
	return (0);
}
