/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-ait-bo <a-ait-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2025/02/20 14:57:28 by a-ait-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

t_texture *load_texture(t_data *data, int *width, int *height, char *path)
{

	t_texture *texture = mlx_xpm_file_to_image(data->mlx->mlx_ptr, path, width, height);
	if (!texture)
	{
		free_scene(data->scene);
		print_error("Error loading texture", __FILE__, __LINE__);
		exit(-1);
	}
	return texture;
}

t_texture *get_textures(t_data *data)
{
	t_texture *textures = (t_texture *)malloc(sizeof(t_texture));
	int width;
	int height;
	if (!textures)
	{
		free_scene(data->scene);
		print_error("Error allocating memory", __FILE__, __LINE__);
		exit(-1);
	}
	textures->north = load_texture(data, &width, &height, data->scene->north_texture);
	textures->north_width = width;
	textures->north_height = height;
	textures->south = load_texture(data, &width, &height, data->scene->south_texture);
	textures->south_width = width;
	textures->south_height = height;
	textures->east = load_texture(data, &width, &height, data->scene->east_texture);
	textures->east_width = width;
	textures->east_height = height;
	textures->west = load_texture(data, &width, &height, data->scene->west_texture);
	textures->west_width = width;
	textures->west_height = height;
	return textures;
}

int	main(int ac, char **av)
{
	t_data data;
	t_scene scene;
	t_mlx	mlx;
	t_player player;
	t_ray	ray;
	t_texture *texture;

	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&scene, 0, sizeof(t_scene));
	ft_memset(&mlx, 0, sizeof(t_mlx));
	ft_memset(&player, 0, sizeof(t_player));
	data.scene = &scene;
	data.mlx = &mlx;
	data.player = &player;
	data.ray = &ray;
	if (ac == 2)
	{
		if (ft_parse(av[1], &data) == -1)
			return(free_scene(&scene), -1);
		else {
			init_game(&data);
			data.texture = get_textures(&data);
			mlx_hook(mlx.win_ptr, 2, 1L<<0, key_pres, &data);
			mlx_hook(mlx.win_ptr, 3, 1L<<1, key_release, &data);
			mlx_hook(mlx.win_ptr, 17, 1L<<1, destroynotify, &data);
			mlx_loop_hook(mlx.mlx_ptr, draw_loop, &data);
			mlx_loop(mlx.mlx_ptr);
		}
		free_scene(&scene);
	}
	else
		return(print_error("Invalid arguments", __FILE__, __LINE__), -1);
	return (0);
}
