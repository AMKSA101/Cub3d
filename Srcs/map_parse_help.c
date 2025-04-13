/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:36:44 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 18:58:23 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	is_valid_zero(char **map, size_t i, size_t j, t_scene *scene)
{
	size_t	map_width;
	size_t	prev_line_width;
	size_t	next_line_width;

	map_width = ft_strlen(map[i]);
	if (j == 0 || j == map_width - 1)
		return (0);
	if (i > 0)
	{
		prev_line_width = ft_strlen(map[i - 1]);
		if (j >= prev_line_width || !is_wall_or_player(map[i - 1][j]))
			return (0);
	}
	if (i + 1 < scene->map_height)
	{
		next_line_width = ft_strlen(map[i + 1]);
		if (j >= next_line_width || !is_wall_or_player(map[i + 1][j]))
			return (0);
	}
	if (!is_wall_or_player(map[i][j - 1]) || !is_wall_or_player(map[i][j + 1]))
		return (0);
	return (1);
}

int	is_wall_or_player(char c)
{
	return (es_wall(c) || is_player(c) || c == '0');
}

int	es_wall(char c)
{
	return (c == '1');
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_space(char c)
{
	return (c == ' ');
}
