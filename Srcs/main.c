/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 09:22:25 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void *load_texture(t_data *data, int *width, int *height, char *path)
{
	void *texture = mlx_xpm_file_to_image(data->mlx->mlx_ptr, path, width, height);
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
	t_texture	*textures;
	int			width;
	int			height;

	textures = (t_texture *)malloc(sizeof(t_texture));
	if (!textures)
	{
		free_scene(data->scene);
		print_error("Error allocating memory for textures", __FILE__, __LINE__);
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

void	mlx_hook_loop(t_data *data)
{
	mlx_hook(data->mlx->win_ptr, KeyPress, KeyPressMask, key_pres, data);
	mlx_hook(data->mlx->win_ptr, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->mlx->win_ptr, DestroyNotify, StructureNotifyMask, destroynotify, data);
	mlx_loop_hook(data->mlx->mlx_ptr, draw_loop, data);
	mlx_loop(data->mlx->mlx_ptr);
}

void	free_all(t_data *data)
{
	if (data->texture)
	{
		if (data->texture->north)
			mlx_destroy_image(data->mlx->mlx_ptr, data->texture->north);
		if (data->texture->south)
			mlx_destroy_image(data->mlx->mlx_ptr, data->texture->south);
		if (data->texture->west)
			mlx_destroy_image(data->mlx->mlx_ptr, data->texture->west);
		if (data->texture->east)
			mlx_destroy_image(data->mlx->mlx_ptr, data->texture->east);
		free(data->texture);
	}
	free_scene(data->scene);
}

int main(int ac, char **av)
{
	t_data		data;
	t_scene		scene;
	t_mlx		mlx;
	t_player	player;
	t_ray		ray;
	
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
		else
		{
			init_game(&data);
			data.texture = get_textures(&data);
			mlx_hook_loop(&data);
		}
		free_all(&data);
	}
	else
		return(1);
}
