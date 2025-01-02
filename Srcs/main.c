/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2025/01/02 11:26:34 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	ft_parse(char *file_name, t_data *data);
int	check_file_extension(char *file_name, char *ext);
int	parse_cube(int fd, int line_count, t_scene *scene);
int	count_lines(char *file_name);
int	check_file_input(char **content, int size, t_scene *scene);
int ft_alloc(char ***arr, int size);
void double_free(char **arr);
int	parse_texture(char **texture, t_scene *scene);
int parse_color(char ** color, t_scene *scene);
int parse_map(char **map, t_scene *scene);
int parse_texture(char **texture, t_scene *scene);
int parse_color(char **color, t_scene *scene);
int parse_map(char **map, t_scene *scene);

int	main(int ac, char **av)
{
	t_data data;
	t_scene scene;

	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&scene, 0, sizeof(t_scene));
	data.scene = &scene;
	if (ac == 2)
	{
		if (ft_parse(av[1], &data) == -1)
			return(-1);
		else
		{
			for (size_t i = 0; i < scene.map_height; i++)
			{
				ft_putstr_fd(scene.map[i], 1);
				ft_putstr_fd("\n", 1);
			}
		}
		// free_scene(scene);
	}
	else
		return(print_error("Invalid arguments", __FILE__, __LINE__), -1);
	return (0);
}

int	ft_parse(char *file_name, t_data *data)
{
	t_scene *scene __attribute_maybe_unused__;
	int line_count;

	scene = data->scene;
	if (check_file_extension(file_name, ".cub") == -1)
		return (-1);

	line_count = count_lines(file_name);
	if (line_count == -1)
		return (-1);
	int fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(print_error(strerror(errno), __FILE__, __LINE__), -1);
	if (parse_cube(fd, line_count, scene) == -1)
		return (-1);
	return (0);
}

int	check_file_extension(char *file_name, char *ext)
{
	size_t len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp(file_name + len - 4, ext, 4) != 0)
		return(print_error("Invalid file extension", __FILE__, __LINE__), -1);
	return (0);
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
		if (line[0] == '\0')
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

int	parse_cube(int fd, int line_count, t_scene *scene __attribute_maybe_unused__)
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
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		content[i++] = ft_strdup(line);
		free(line);
	}
	close(fd);
	if (check_file_input(content, line_count, scene) == -1)
	{
		double_free(content);
		return (-1);
	}
	double_free(content);
	return (0);
}

int check_file_input(char **content, int size, t_scene *scene )
{
	char **texture;
	char **color;
	char **map;
	int i;

	i = 0;
	if (ft_alloc(&texture, 4) == -1)
		return (-1);
	if (ft_alloc(&color, 2) == -1)
	{
		double_free(texture);
		return (-1);
	}
	if (ft_alloc(&map, size - 6) == -1)
	{
		double_free(texture);
		double_free(color);
		return (-1);
	}
	while (i < size)
	{
		if (i < 4)
			texture[i] = ft_strdup(content[i]);
		else if (i < 6)
			color[i - 4] = ft_strdup(content[i]);
		else
			map[i - 6] = ft_strdup(content[i]);
		i++;
	}
	if (parse_texture(texture, scene) == -1)
		return (double_free(texture), double_free(color), double_free(map), -1);
	if (parse_color(color, scene) == -1)
		return (double_free(texture), double_free(color), double_free(map), -1);
	if (parse_map(map, scene) == -1)
		return (double_free(texture), double_free(color), double_free(map), -1);
	return (double_free(texture), double_free(color), double_free(map), 0);
}

int	parse_texture(char **texture, t_scene *scene __attribute_maybe_unused__)
{
	printf("Texture is this way:\n");
	for (int i = 0; i < 4; i++)
	{
		printf("%s\n\n", texture[i]);
	}
	return (0);
}

int	parse_color(char **color, t_scene *scene __attribute_maybe_unused__)
{
	printf("Color is this way:\n");
	for (int i = 0; i < 2; i++)
	{
		printf("%s\n\n", color[i]);
	}
	return (0);
}

int	parse_map(char **map, t_scene *scene __attribute_maybe_unused__)
{
	printf("Map is designed is follows:\n");
	for (int i = 0; i < 14; i++)
	{
		printf("%s\n\n", map[i]);
	}
	return (0);
}

int ft_alloc(char ***arr, int size)
{
	int i;

	i = 0;
	*arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!*arr)
	{
		print_error(strerror(errno), __FILE__, __LINE__);
		return(-1);
	}
	while (i < size)
	{
		(*arr)[i] = NULL;
		i++;
	}
	(*arr)[i] = NULL;
	return (0);
}

void double_free(char **arr)
{
	int i;

	if (arr == NULL)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

