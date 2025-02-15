/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by abamksa           #+#    #+#             */
/*   Updated: 2025/02/15 10:30:14 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	ft_parse(char *file_name, t_data *data)
{
	t_scene *scene __attribute_maybe_unused__;
	int line_count;

	scene = data->scene;
	if (check_file_extension(file_name, ".cub") == -1)
		return (print_error("Invalid file extension", __FILE__, __LINE__), -1);
	line_count = count_lines(file_name);
	if (line_count == -1)
		return (-1);
	int fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(print_error(strerror(errno), __FILE__, __LINE__), -1);
	if (parse_cube(fd, line_count, data, scene) == -1)
		return (-1);
	return (0);
}

int	parse_cube(int fd, int line_count, t_data *data, t_scene *scene __attribute_maybe_unused__)
{
	char **content;
	char *line;
	int i;

	if (ft_alloc(&content, line_count) == -1)
		return (-1);
	line = NULL;
	i = 0;
	while ((get_next_line(fd, &line)) >= 0)
	{
		if (check_empty_line(line) == 1 || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue;
		}
		content[i++] = ft_strdup(line);
		free(line);
	}
	close(fd);
	if (check_file_input(content, line_count, data, scene) == -1)
	{
		double_free(content);
		return (-1);
	}
	double_free(content);
	return (0);
}

int	check_empty_line(char *line)
{
	int i;

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
	int fd;
	int line_count;
	char *line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(print_error(strerror(errno), __FILE__, __LINE__), -1);
	line_count = 0;
	while ((get_next_line(fd, &line)) >= 0)
	{
		if (check_empty_line(line) == 1 || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue;
		}
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}



int check_file_input(char **content, int size, t_data *data, t_scene *scene )
{
	char **texture;
	char **color;
	char **map;
	int	map_start;
	int i;

	i = 0;
	map_start = -1;
	if (ft_alloc(&texture, 4) == -1)
		return (-1);
	if (ft_alloc(&color, 2) == -1)
	{
		double_free(texture);
		return (-1);
	}
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
	if (ft_alloc(&map, size - map_start) == -1)
	{
		double_free(texture);
		double_free(color);
		return (-1);
	}
	// Copy texture and color lines
	int texture_index = 0;
	int color_index = 0;

	for (i = 0; i < map_start; i++) //for loop needs to be changed to while loop
	{
		if (texture_index < 4 && (ft_strncmp(content[i], "NO", 2) == 0 || ft_strncmp(content[i], "SO", 2) == 0 || ft_strncmp(content[i], "WE", 2) == 0 || ft_strncmp(content[i], "EA", 2) == 0))
		{
			texture[texture_index] = ft_strdup(content[i]);
			texture_index++;
		}
		else if (color_index < 2 && (ft_strncmp(content[i], "F", 1) == 0 || ft_strncmp(content[i], "C", 1) == 0))
		{
			color[color_index] = ft_strdup(content[i]);
			color_index++;
		}
		else
			return (double_free(texture), double_free(color), double_free(map), print_error("Invalid texture/color arguments", __FILE__, __LINE__), -1);
	}
	// Copy map lines
	for (i = 0; i < (size - map_start); i++)//for loop needs to be changed to while loop
	{
		map[i] = ft_strdup(content[map_start + i]);
	}
	if (parse_texture(texture, data, scene) == -1)
		return (double_free(texture), double_free(color), double_free(map), -1);
	if (parse_color(color, scene) == -1)
		return (double_free(texture), double_free(color), double_free(map), -1);
	if (parse_map(map, scene) == -1)
		return (double_free(texture), double_free(color), double_free(map), -1);
	scene->map_width = ft_strlen(scene->map[0]); // Initialize map_width after parsing map
	for (size_t i = 1; scene->map[i]; ++i) {
		size_t current_width = ft_strlen(scene->map[i]);
		if (scene->map_width < current_width)
			scene->map_width = current_width;
	}
	return (double_free(texture), double_free(color), 0);
}

