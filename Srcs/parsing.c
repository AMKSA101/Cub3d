/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 19:23:58 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	ft_parse(char *file_name, t_data *data)
{
	t_scene	*scene;
	int		line_count;
	int		fd;

	scene = data->scene;
	if (check_file_extension(file_name, ".cub") == -1)
		return (print_error("Invalid file extension", __FILE__, __LINE__), -1);
	line_count = count_lines(file_name);
	if (line_count == -1)
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (print_error(strerror(errno), __FILE__, __LINE__), -1);
	if (parse_cube(fd, line_count, data, scene) == -1)
		return (-1);
	return (0);
}

int	parse_cube(int fd, int line_count, t_data *data, t_scene *scene)
{
	char	**content;
	char	*line;
	int		i;

	if (ft_alloc(&content, line_count) == -1)
		return (-1);
	line = NULL;
	i = 0;
	while ((get_next_line(fd, &line)) >= 0)
	{
		if (check_empty_line(line) == 1 || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		content[i++] = ft_strdup(line);
		free(line);
	}
	close(fd);
	if (check_file_input(content, line_count, data, scene) == -1)
		return (double_free(content), -1);
	double_free(content);
	return (0);
}

int	check_file_input(char **content, int size, t_data *data, t_scene *scene)
{
	char	**texture;
	char	**color;
	char	**map;
	int		map_start;
	int		vars[2];

	vars[0] = size;
	map_start = find_map_start(content, size);
	if (map_start == -1)
		return (-1);
	vars[1] = map_start;
	if (allocate_components(&texture, &color, &map, vars) == -1)
		return (-1);
	if (extract_textures_and_colors(content, map_start, texture, color) == -1)
		return (double_free(texture), double_free(color), double_free(map),
			print_error("Invalid texture/color arguments", __FILE__, __LINE__),
			-1);
	copy_map_data(content, map_start, size, map);
	if (parse_texture(texture, data, scene) == -1
		|| parse_color(color, scene) == -1
		|| parse_map(map, scene) == -1)
		return (double_free(texture), double_free(color), double_free(map), -1);
	calculate_map_width(scene);
	return (double_free(texture), double_free(color), 0);
}
