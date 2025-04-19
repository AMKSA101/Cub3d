/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:38:54 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/15 16:29:03 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

static void	init_scene_data(t_scene *scene);
static int	validate_texture_parts(char **parts);
static char	*join_path_parts(char **parts, int count, int i);

int	parse_texture(char **texture, t_data *data, t_scene *scene)
{
	int	i;

	data->scene = scene;
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

static void	init_scene_data(t_scene *scene)
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

int	parse_texture_line(char *line, t_scene *scene)
{
	char	**parts;
	int		fd;

	if (!line)
		return (print_error("Texture line is NULL", __FILE__, __LINE__), -1);
	parts = ft_split(line, ' ');
	if (!parts)
		return (print_error(strerror(errno), __FILE__, __LINE__), -1);
	if (validate_texture_parts(parts) == -1)
		return (-1);
	fd = open(parts[1], O_RDONLY);
	if (fd == -1)
		return (double_free(parts),
			print_error("Cannot open texture file", __FILE__, __LINE__), -1);
	if (check_file_extension(parts[1], ".xpm") == -1)
		return (close(fd), double_free(parts),
			print_error("Invalid texture extension", __FILE__, __LINE__), -1);
	if (set_texture_path(parts, scene, fd) == -1)
		return (-1);
	return (0);
}

static char	*join_path_parts(char **parts, int count, int i)
{
	char	*fixed_path;
	char	*temp;

	fixed_path = ft_strdup(parts[1]);
	while (i < count)
	{
		temp = fixed_path;
		fixed_path = ft_strjoin(temp, " ");
		free(temp);
		temp = fixed_path;
		fixed_path = ft_strjoin(temp, parts[i]);
		free(temp);
		i++;
	}
	free(parts[1]);
	parts[1] = fixed_path;
	parts[2] = NULL;
	return (0);
}

static int	validate_texture_parts(char **parts)
{
	int	count;

	if (!parts)
		return (print_error("Parts array is NULL", __FILE__, __LINE__), -1);
	count = 0;
	while (parts[count])
		count++;
	if (count < 2)
		return (double_free(parts),
			print_error("Invalid texture line format", __FILE__, __LINE__), -1);
	if (count > 2)
		join_path_parts(parts, count, 2);
	return (0);
}
