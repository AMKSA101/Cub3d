/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:38:54 by abamksa           #+#    #+#             */
/*   Updated: 2025/02/15 11:04:05 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

static void init_scene_data(t_scene *scene);

int parse_texture(char **texture, t_data *data, t_scene *scene)
{
	int i;
	data->scene = scene;

	init_scene_data(scene);
	if (!texture)
		return (print_error("Texture array is NULL", __FILE__, __LINE__), -1);

	for (i = 0; i < 4 && texture[i]; i++)
	{
		if (parse_texture_line(texture[i], scene) == -1)
			return -1;
	}
	if (i != 4)
		return (print_error("Invalid texture amount", __FILE__, __LINE__), -1);
	return 0;
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

int parse_texture_line(char *line, t_scene *scene)
{
	char **parts;
	int count;

	if (!line)
		return (print_error("Texture line is NULL", __FILE__, __LINE__), -1);

	parts = ft_split(line, ' ');
	if (!parts)
		return (print_error(strerror(errno), __FILE__, __LINE__), -1);

	for (count = 0; parts[count]; count++);

	if (count != 2)
		return (double_free(parts), print_error("Invalid texture line format", __FILE__, __LINE__), -1);

	if (ft_strncmp(parts[0], "NO", 3) == 0 && check_file_extension(parts[1], ".xpm") == 0 && open(parts[1], O_RDONLY) != -1)
		scene->north_texture = ft_strdup(parts[1]);
	else if (ft_strncmp(parts[0], "SO", 3) == 0 && check_file_extension(parts[1], ".xpm") == 0 && open(parts[1], O_RDONLY) != -1)
		scene->south_texture = ft_strdup(parts[1]);
	else if (ft_strncmp(parts[0], "EA", 3) == 0 && check_file_extension(parts[1], ".xpm") == 0 && open(parts[1], O_RDONLY) != -1)
		scene->east_texture = ft_strdup(parts[1]);
	else if (ft_strncmp(parts[0], "WE", 3) == 0 && check_file_extension(parts[1], ".xpm") == 0 && open(parts[1], O_RDONLY) != -1)
		scene->west_texture = ft_strdup(parts[1]);
	else
		return (double_free(parts), print_error("Invalid texture file", __FILE__, __LINE__), -1);

	return (double_free(parts), 0);
}
