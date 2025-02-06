/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:33:10 by abamksa           #+#    #+#             */
/*   Updated: 2025/02/04 12:36:38 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int is_valid_zero(char **map, size_t i, size_t j, t_scene *scene);
int is_wall_or_player(char c);
int es_wall(char c);
int is_player(char c);
int is_space(char c);

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

//helper for map parsing
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
	size_t j;
	size_t player_count;

	if (!map)
		return (print_error("Map array is NULL", __FILE__, __LINE__), -1);
	player_count = 0;
	i = 0;
	if (check_borders(map, scene) == -1)
		return (print_error("Invalid map border", __FILE__, __LINE__), -1);
	while (map[i])
	{
		j = 0;
		size_t map_width = ft_strlen(map[i]);
		while (j < map_width)
		{
			if (is_player(map[i][j]))
			{
				player_count++;
				scene->player_start_dir = map[i][j];
				scene->player_start_x = (double)j;
				scene->player_start_y = (double)i;
			}
			else if (map[i][j] == '0')
			{
				if (!is_valid_zero(map, i, j, scene))
					return (print_error("Invalid map format", __FILE__, __LINE__), -1);
			}
			else if (!es_wall(map[i][j]) && !is_space(map[i][j]))
				return (print_error("Invalid map format", __FILE__, __LINE__), -1);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return(print_error("Wrong player count", __FILE__, __LINE__), -1);
	return (0);
}

int is_valid_zero(char **map, size_t i, size_t j, t_scene *scene) {
	size_t map_width;
	size_t prev_line_width;
	size_t next_line_width;

	map_width = ft_strlen(map[i]);

	// Boundary checks for current line
	if (j == 0 || j == map_width - 1) return 0;

	// Check above line
	if (i > 0) {
		prev_line_width = ft_strlen(map[i - 1]);
		if (j >= prev_line_width || !is_wall_or_player(map[i - 1][j])) return 0;
	}

	// Check below line
	if (i + 1 < scene->map_height) {
		next_line_width = ft_strlen(map[i + 1]);
		if (j >= next_line_width || !is_wall_or_player(map[i + 1][j])) return 0;
	}

	// Check adjacent tiles in the current line
	if (!is_wall_or_player(map[i][j - 1]) || !is_wall_or_player(map[i][j + 1])) return 0;

	return 1; // Valid '0'
}


int is_wall_or_player(char c)
{
	return es_wall(c) || is_player(c) || c == '0';
}

int es_wall(char c)
{
	return c == '1';
}


int is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}



int is_space(char c) {
	return c == ' ';
}
/*map example

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
1111111110110000011100001
1000000000110000011111111
100S001111011100000010001
1100011111011101010010001
10000001101010110000000000010001
1000000000000000000010001
1000000000000000110000001
1100000111010101111110111
1111011111101011011110001
1111111111111111111111111
*/
