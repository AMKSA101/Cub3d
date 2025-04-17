/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/17 13:18:04 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	*load_texture(t_data *data, int *width, int *height, char *path)
{
	void	*texture;

	if (!path)
	{
		print_error("Texture path is NULL", __FILE__, __LINE__);
		if (data->texture)
			free(data->texture);
		free_scene(data->scene);
		exit(1);
	}
	texture = mlx_xpm_file_to_image(data->mlx->mlx_ptr, path, width, height);
	if (!texture)
	{
		print_error("Error loading texture", __FILE__, __LINE__);
		if (data->texture)
			free(data->texture);
		free_scene(data->scene);
		exit(1);
	}
	return (texture);
}

void	texture_load(t_data *data, t_texture *textures)
{
	int	width;
	int	height;

	textures->north = load_texture(data, &width, &height,
			data->scene->north_texture);
	textures->north_width = width;
	textures->north_height = height;
	textures->south = load_texture(data, &width, &height,
			data->scene->south_texture);
	textures->south_width = width;
	textures->south_height = height;
	textures->east = load_texture(data, &width, &height,
			data->scene->east_texture);
	textures->east_width = width;
	textures->east_height = height;
	textures->west = load_texture(data, &width, &height,
			data->scene->west_texture);
	textures->west_width = width;
	textures->west_height = height;
}

static t_texture	*get_textures(t_data *data)
{
	t_texture	*textures;

	textures = (t_texture *)malloc(sizeof(t_texture));
	if (!textures)
	{
		print_error("Error allocating memory for textures", __FILE__, __LINE__);
		destroynotify(data);
		return (NULL);
	}
	texture_load(data, textures);
	if (!textures->north || !textures->south
		|| !textures->east || !textures->west)
	{
		free(textures);
		return (NULL);
	}
	return (textures);
}

void	mlx_hook_loop(t_data *data)
{
	mlx_hook(data->mlx->win_ptr, KeyPress, KeyPressMask, key_pres, data);
	mlx_hook(data->mlx->win_ptr, KeyRelease, KeyReleaseMask,
		key_release, data);
	mlx_hook(data->mlx->win_ptr, DestroyNotify, StructureNotifyMask,
		destroynotify, data);
	mlx_loop_hook(data->mlx->mlx_ptr, draw_loop, data);
	mlx_loop(data->mlx->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_scene		scene;
	t_mlx		mlx;
	t_player	player;
	t_ray		ray;

	init_data(&data, &scene, &mlx, &player);
	data.ray = &ray;
	if (ac == 2)
	{
		if (ft_parse(av[1], &data) == -1)
		{
			free_scene(&scene);
			return (-1);
		}
		init_game(&data);
		data.texture = get_textures(&data);
		if (!data.texture)
		{
			free_scene(&scene);
			return (-1);
		}
		mlx_hook_loop(&data);
		free_all(&data);
	}
	else
		return (1);
	return (0);
}
