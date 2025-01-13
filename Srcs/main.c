/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2025/01/13 11:07:44 by abamksa          ###   ########.fr       */
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
static int parse_texture_line(char *line, t_scene *scene);
static int parse_color_line(char *line, t_scene *scene);
static int check_map_line(char *line);
static int parse_rgb_values(char *str, int *r, int *g, int *b);
static void init_scene_data(t_scene *scene);
static int check_map_valid(char **map, t_scene *scene);
void free_scene(t_scene *scene);
int	check_empty_line(char *line);
int	check_separator(char *str, char c);


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
			return(free_scene(&scene), -1);
		else
		{
			ft_putstr_fd("Parsing successful\n", 1);
		}
		free_scene(&scene);
	}
	else
		return(print_error("Invalid arguments", __FILE__, __LINE__), -1);
	return (0);
}

void free_scene(t_scene *scene)
{
	if (scene == NULL)
		return;
	free(scene->north_texture);
	free(scene->south_texture);
	free(scene->west_texture);
	free(scene->east_texture);
	double_free(scene->map);
}

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
	if (parse_cube(fd, line_count, scene) == -1)
		return (-1);
	return (0);
}

int	check_file_extension(char *file_name, char *ext)
{
	size_t len = ft_strlen(file_name);
	size_t size = ft_strlen(ext);
	if (len < 4 || ft_strncmp(file_name + len - size, ext, size) != 0)
		return(-1);
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
		if (check_empty_line(line) == 1 || line[0] == '\0' || line[0] == '\n')
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

int check_file_input(char **content, int size, t_scene *scene )
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
	for (i = 0; i < map_start; i++)
	{
		if (i < 4)
			texture[i] = ft_strdup(content[i]);
		else if (i < 6)
			color[i - 4] = ft_strdup(content[i]);
	}
	// Copy map lines
	for (i = 0; i < (size - map_start); i++)
	{
		map[i] = ft_strdup(content[map_start + i]);
	}
	if (parse_texture(texture, scene) == -1)
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

// Texture Parsing function
int	parse_texture(char **texture, t_scene *scene)
{
	int i;

	init_scene_data(scene);
	if (!texture)
		return (print_error("Texture array is NULL", __FILE__, __LINE__), -1);
	i = 0;
	while (i < 4 && texture[i])
	{
		if (parse_texture_line(texture[i], scene) == -1)
			return (-1);
		i++;
	}
	if (i != 4)
		return (print_error("Invalid texture amount", __FILE__, __LINE__), -1);
	return (0);
}

static void init_scene_data(t_scene *scene)
{
	scene->north_texture = NULL;
	scene->south_texture = NULL;
	scene->east_texture = NULL;
	scene->west_texture = NULL;
	scene->floor_color = 0;
	scene->ceiling_color = 0;
	scene->map = NULL;
	scene->map_height = 0;
}

// helper function for textures
static int parse_texture_line(char *line, t_scene *scene)
{
	char **parts;
	int count;

	if (!line)
		return (print_error("Texture line is NULL", __FILE__, __LINE__), -1);
	parts = ft_split(line, ' ');
	if (!parts)
		return(print_error(strerror(errno), __FILE__, __LINE__), -1);
	count = 0;
	while (parts[count])
		count++;
	if (count != 2)
		return (double_free(parts),print_error("Invalid texture line format", __FILE__, __LINE__), -1);
	if (ft_strncmp(parts[0], "NO", 3) == 0 && check_file_extension(parts[1], ".xpm") == 0 && open(parts[1], O_RDONLY) != -1)
		scene->north_texture = ft_strdup(parts[1]);
	else if (ft_strncmp(parts[0], "SO", 3) == 0 && check_file_extension(parts[1], ".xpm") == 0 && open(parts[1], O_RDONLY) != -1)
		scene->south_texture = ft_strdup(parts[1]);
	else if (ft_strncmp(parts[0], "EA", 3) == 0 && check_file_extension(parts[1], ".xpm") == 0 && open(parts[1], O_RDONLY) != -1)
		scene->east_texture = ft_strdup(parts[1]);
	else if (ft_strncmp(parts[0], "WE", 3) == 0 && check_file_extension(parts[1], ".xpm") == 0 && open(parts[1], O_RDONLY) != -1)
		scene->west_texture = ft_strdup(parts[1]);
	else
		return (double_free(parts),print_error("Invalid texture file", __FILE__, __LINE__), -1);
	return (double_free(parts), 0);
}

// Color parsing function
int	parse_color(char **color, t_scene *scene)
{
	int i;

	if (!color)
		return (print_error("color array is NULL", __FILE__, __LINE__), -1);
	i = 0;
	while (i < 2 && color[i])
	{
		if (parse_color_line(color[i], scene) == -1)
			return (-1);
		i++;
	}
	if (i != 2)
		return (print_error("Invalid color amount", __FILE__, __LINE__), -1);
	return (0);
}

//helper function for color
static int parse_color_line(char *line, t_scene *scene)
{
	char **parts;
	int count;
	int rgb[3];

	if (!line)
		return (print_error("color line is NULL", __FILE__, __LINE__), -1);
	parts = ft_split(line, ' ');
	if (!parts)
		return(print_error(strerror(errno), __FILE__, __LINE__), -1);
	if (check_separator(parts[1], ',') == -1)
		return(double_free(parts), -1);
	count = 0;
	while (parts[count])
		count++;
	if (count != 2)
		return (double_free(parts), print_error("Invalid color line format", __FILE__, __LINE__), -1);
	if (ft_strncmp(parts[0], "F", 2) == 0)
	{
		if (parse_rgb_values(parts[1], &rgb[0], &rgb[1], &rgb[2]) == -1)
			return(double_free(parts), -1);
		scene->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	}
	else if (ft_strncmp(parts[0], "C", 2) == 0)
	{
		if (parse_rgb_values(parts[1], &rgb[0], &rgb[1], &rgb[2]) == -1)
			return (double_free(parts), -1);
		scene->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	}
	else
		return (double_free(parts), print_error("Invalid color identifier", __FILE__, __LINE__), -1);
	return (double_free(parts), 0);
}

int	check_separator(char *str, char c)
{
	int i;
	int count;

	if (!str)
		return (print_error("Separator string is NULL", __FILE__, __LINE__), -1);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count != 2)
		return (print_error("Invalid separator count", __FILE__, __LINE__), -1);
	return (0);
}

static int parse_rgb_values(char *str, int *r, int *g, int *b)
{
	char **rgb_strs;
	int count;
	int temp_rgb[3];

	if (!str)
		return (print_error("RGB string is NULL", __FILE__, __LINE__), -1);
	rgb_strs = ft_split(str, ',');
	if (!rgb_strs)
		return (print_error(strerror(errno), __FILE__, __LINE__), -1);
	count = 0;
	while (rgb_strs[count])
		count++;
	if (count != 3)
		return(double_free(rgb_strs), print_error("Invalid RGB format", __FILE__, __LINE__), -1);
	temp_rgb[0] = ft_atoi(rgb_strs[0]);
	temp_rgb[1] = ft_atoi(rgb_strs[1]);
	temp_rgb[2] = ft_atoi(rgb_strs[2]);
	if (temp_rgb[0] < 0 || temp_rgb[0] > 255 || temp_rgb[1] < 0 || temp_rgb[1] > 255 || temp_rgb[2] < 0 || temp_rgb[2] > 255)
		return (double_free(rgb_strs), print_error("Invalid RGB value range", __FILE__, __LINE__), -1);
	*r = temp_rgb[0];
	*g = temp_rgb[1];
	*b = temp_rgb[2];
	return(double_free(rgb_strs), 0);
}

// Map parsing function
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
	scene->map = map;
	if (check_map_valid(map, scene) == -1)
		return (-1);
	return (0);
}

//helper for map parsing
static int check_map_line(char *line)
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


static int check_map_valid(char **map, t_scene *scene)
{
	int i;
	int j;
	int player_count;

	if (!map)
		return (print_error("Map array is NULL", __FILE__, __LINE__), -1);
	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				player_count++;
				scene->player_start_dir = map[i][j];
				scene->player_start_x = (double)j;
				scene->player_start_y = (double)i;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return(print_error("Wrong player count", __FILE__, __LINE__), -1);
	return (0);
}
