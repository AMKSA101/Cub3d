/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:38:54 by abamksa           #+#    #+#             */
/*   Updated: 2025/01/16 15:40:56 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

static void init_scene_data(t_scene *scene);

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
int parse_texture_line(char *line, t_scene *scene)
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
