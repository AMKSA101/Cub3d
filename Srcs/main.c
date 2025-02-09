/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-ait-bo <a-ait-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2025/02/06 12:17:21 by a-ait-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void print_scene(t_scene *scene){
	ft_putstr_fd("North texture: ", 1);
	ft_putendl_fd(scene->north_texture, 1);
	ft_putstr_fd("South texture: ", 1);
	ft_putendl_fd(scene->south_texture, 1);
	ft_putstr_fd("West texture: ", 1);
	ft_putendl_fd(scene->west_texture, 1);
	ft_putstr_fd("East texture: ", 1);
	ft_putendl_fd(scene->east_texture, 1);
	ft_putstr_fd("Floor color: ", 1);
	ft_putnbr_fd(scene->floor_color, 1);
	ft_putstr_fd("\nCeiling color: ", 1);
	ft_putnbr_fd(scene->ceiling_color, 1);
	ft_putstr_fd("\nMap:\n", 1);
	for (size_t i = 0; i < scene->map_height; i++)
	{
		ft_putendl_fd(scene->map[i], 1);
	}
	ft_putstr_fd("Player start direction: ", 1);
	ft_putchar_fd(scene->player_start_dir, 1);
	ft_putstr_fd("\nPlayer start x: ", 1);
	ft_putnbr_fd(scene->player_start_x, 1);
	ft_putstr_fd("\nPlayer start y: ", 1);
	ft_putnbr_fd(scene->player_start_y, 1);
}

t_texture *load_texture(t_data *data, char *path, const char *texture_name)
{
	int width = WIDTH;
	int height = HEIGHT;
	t_texture *texture = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if (!texture)
	{
		free_scene(data->scene);
		print_error("Error loading texture", __FILE__, __LINE__);
		exit(-1);
	}
	return texture;
}

t_texture *load_textures(t_data *data)
{
	t_texture *textures = (t_texture *)malloc(sizeof(t_texture));
	if (!textures)
	{
		free_scene(data->scene);
		print_error("Error allocating memory", __FILE__, __LINE__);
		exit(-1);
	}
	textures->north = load_texture(data, data->scene->north, "north");
	textures->south = load_texture(data, data->scene->south, "south");
	textures->east = load_texture(data, data->scene->east, "east");
	textures->west = load_texture(data, data->scene->west, "west");
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
			// ft_putstr_fd("Parsing successful\n", 1);
			// ft_putstr_fd("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", 1);
			// print_scene(&scene);
			init_game(&data);
			mlx_hook(mlx.win_ptr, 2, 1L<<0, key_pres, &data);
			mlx_hook(mlx.win_ptr, 3, 1L<<1, key_release, &data);
			mlx_loop_hook(mlx.mlx_ptr, draw_loop, &data);
			mlx_loop(mlx.mlx_ptr);
			// start_game(&scene);
		}
		free_scene(&scene);
	}
	else
		return(print_error("Invalid arguments", __FILE__, __LINE__), -1);
	return (0);
}
