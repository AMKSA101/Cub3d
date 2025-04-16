/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:27:02 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/16 19:20:25 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	allocate_components(char ***texture, char ***color, char ***map, int *vars)
{
	int	size;
	int	map_start;

	size = vars[0];
	map_start = vars[1];
	if (ft_alloc(texture, 4) == -1)
		return (print_error("Memory allocation failed",
				__FILE__, __LINE__), -1);
	if (ft_alloc(color, 2) == -1)
		return (double_free(*texture),
			print_error("Memory allocation failed", __FILE__, __LINE__), -1);
	if (ft_alloc(map, size - map_start) == -1)
		return (double_free(*texture), double_free(*color),
			print_error("Memory allocation failed", __FILE__, __LINE__), -1);
	return (0);
}

int	assign_texture(char **parts, t_scene *scene, char *path)
{
	if (ft_strncmp(parts[0], "NO", 3) == 0)
	{
		if (scene->north_texture)
			free(scene->north_texture);
		scene->north_texture = ft_strdup(path);
	}
	else if (ft_strncmp(parts[0], "SO", 3) == 0)
	{
		if (scene->south_texture)
			free(scene->south_texture);
		scene->south_texture = ft_strdup(path);
	}
	else if (ft_strncmp(parts[0], "EA", 3) == 0)
	{
		if (scene->east_texture)
			free(scene->east_texture);
		scene->east_texture = ft_strdup(path);
	}
	else if (ft_strncmp(parts[0], "WE", 3) == 0)
	{
		if (scene->west_texture)
			free(scene->west_texture);
		scene->west_texture = ft_strdup(path);
	}
	else
		return (-1);
	return (0);
}

int	set_texture_path(char **parts, t_scene *scene, int fd)
{
	char	*path;
	int		path_len;
	int		i;

	path = parts[1];
	path_len = ft_strlen(path);
	i = path_len - 1;
	while (i >= 0)
	{
		if (ft_isalnum(path[i]) || path[i] == '.' || path[i] == '/'
			|| path[i] == '-' || path[i] == '_')
			break ;
		i--;
	}
	if (i < path_len - 1)
		path[i + 1] = '\0';
	if (assign_texture(parts, scene, path) == -1)
		return (close(fd), double_free(parts),
			print_error("Invalid texture identifier", __FILE__, __LINE__), -1);
	return (close(fd), double_free(parts), 0);
}
