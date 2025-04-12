/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:05:00 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 19:08:15 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

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
			(*player_count)++;
			scene->player_start_dir = map[i][j];
			scene->player_start_x = (double)j;
			scene->player_start_y = (double)i;
		}
		else if (map[i][j] == '0')
		{
			if (!is_valid_zero(map, i, j, scene))
				return (print_error("Invalid map format", __FILE__, __LINE__),
					-1);
		}
		else if (!es_wall(map[i][j]) && !is_space(map[i][j]))
			return (print_error("Invalid map format", __FILE__, __LINE__), -1);
		j++;
	}
	return (0);
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
