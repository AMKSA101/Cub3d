/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:05:00 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/15 15:53:00 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	check_player_position(char **map, size_t i, size_t j, t_scene *scene)
{
	size_t	map_width;

	map_width = ft_strlen(map[i]);
	if (j == 0 || j == map_width - 1 || i == 0
		|| i == scene->map_height - 1)
		return (print_error("Player cannot be at map edge",
				__FILE__, __LINE__), -1);
	if ((i > 0 && (j >= ft_strlen(map[i - 1])
				|| map[i - 1][j] == ' '))
		|| (i + 1 < scene->map_height && (j >= ft_strlen(map[i + 1])
				|| map[i + 1][j] == ' '))
		|| (j > 0 && map[i][j - 1] == ' ')
		|| (j + 1 < map_width && map[i][j + 1] == ' '))
		return (print_error("Player cannot be adjacent to space",
				__FILE__, __LINE__), -1);
	return (0);
}

int	validate_map_character(char **map, size_t i, size_t j, t_scene *scene)
{
	if (map[i][j] == '0')
	{
		if (!is_valid_zero(map, i, j, scene))
			return (print_error("Invalid map format", __FILE__, __LINE__), -1);
	}
	else if (!es_wall(map[i][j]) && !is_space(map[i][j])
		&& !is_player(map[i][j]))
		return (print_error("Invalid map format", __FILE__, __LINE__), -1);
	return (0);
}

int	process_map_line(char **map, size_t i, size_t *player_count, t_scene *scene)
{
	size_t	j;
	size_t	map_width;

	j = 0;
	map_width = ft_strlen(map[i]);
	while (j < map_width)
	{
		if (is_player(map[i][j]))
		{
			if (check_player_position(map, i, j, scene) == -1)
				return (-1);
			(*player_count)++;
			scene->player_start_dir = map[i][j];
			scene->player_start_x = (double)j;
			scene->player_start_y = (double)i;
		}
		else if (validate_map_character(map, i, j, scene) == -1)
			return (-1);
		j++;
	}
	return (0);
}

int	count_lines(char *file_name)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (print_error(strerror(errno), __FILE__, __LINE__), -1);
	line_count = 0;
	while ((get_next_line(fd, &line)) >= 0)
	{
		if (check_empty_line(line) == 1 || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}

void	init_data(t_data *data, t_scene *scene, t_mlx *mlx, t_player *player)
{
	ft_memset(data, 0, sizeof(t_data));
	ft_memset(scene, 0, sizeof(t_scene));
	ft_memset(mlx, 0, sizeof(t_mlx));
	ft_memset(player, 0, sizeof(t_player));
	data->scene = scene;
	data->mlx = mlx;
	data->player = player;
}
