/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:54:38 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/03/07 10:54:31 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	init_game(t_data *data)
{
	t_scene	*img;
	t_mlx	*mlx;

	mlx = data->mlx;
	img = data->scene;
	init_player_position(data->player, data->scene);
	init_player(data->player, data->scene);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "test");
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &img->bits_per_pixel, \
									&img->line_length, &img->endian);
}

void	init_player_position(t_player *player, t_scene *img)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = img->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S')
			{
				player->x = j * BLOCK;
				player->y = i * BLOCK;
			}
			j++;
		}
		i++;
	}
}

void	init_player(t_player *player, t_scene *img)
{
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->speed_rotate = false;
	player->speed = 0.2;
}
