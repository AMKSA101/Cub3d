/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2025/01/22 11:40:31 by abamksa          ###   ########.fr       */
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
		else {
			// ft_putstr_fd("Parsing successful\n", 1);
			// ft_putstr_fd("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", 1);
			// print_scene(&scene);
			init_game(&scene);
			mlx_hook(scene.win_ptr, 2, 1L<<0, key_pres, &scene.player);
			mlx_hook(scene.win_ptr, 3, 1L<<1, key_release, &scene.player);
			mlx_loop_hook(scene.mlx_ptr, draw_loop, &scene);
			mlx_loop(scene.mlx_ptr);
			// start_game(&scene);
		}
		free_scene(&scene);
	}
	else
		return(print_error("Invalid arguments", __FILE__, __LINE__), -1);
	return (0);
}
