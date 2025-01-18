/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2025/01/18 18:39:29 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int init_player(t_data *data)
{
	t_player *player;

	player = &data->player;
	player->x = data->scene->player_start_x;
	player->y = data->scene->player_start_y;
	if (data->scene->player_start_dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (data->scene->player_start_dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (data->scene->player_start_dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (data->scene->player_start_dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	return (0);
}

int init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return(print_error("Failed to initialize MLX", __FILE__, __LINE__), -1);
	data->win = mlx_new_window(data->mlx, data->scene->map_width * 32, data->scene->map_height * 32, "Cub3D");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		return(print_error("Failed to create window", __FILE__, __LINE__), -1);
	}
	return (0);
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
		else
		{
			ft_putstr_fd("Parsing successful\n", 1);
			if (init_player(&data) == -1)
				return(free_scene(&scene), -1);
			ft_putstr_fd("Player initialized\n", 1);
			if (init_mlx(&data) == -1)
				return(free_scene(&scene), -1);
			ft_putstr_fd("MLX initialized\n", 1);
			mlx_loop(data.mlx);
		}
		mlx_destroy_display(data.mlx);
		free_scene(&scene);
	}
	else
		return(print_error("Invalid arguments", __FILE__, __LINE__), -1);
	return (0);
}
