/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:54:38 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/04/14 12:46:18 by abamksa          ###   ########.fr       */
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
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &img->bits_per_pixel,
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
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' )
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
	// if ( == 'E')
		// player->angle = PI;
	// if ( == 'S')
		// player->angle = 3 * PI / 2;
	// if ( == 'W')
		// player->angle = 2 * PI;
	// if ( == 'N')
		// player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->speed_rotate = false;
	player->speed = 0.2;
}

void	direction_of_player(t_scene *img, t_player *player)
{
	if (player->key_up)
	{
		player->new_x -= player->cos_angle * player->speed;
		player->new_y -= player->sin_angle * player->speed;
	}
	if (player->key_down)
	{
		player->new_x += player->cos_angle * player->speed;
		player->new_y += player->sin_angle * player->speed;
	}
	if (player->key_left)
	{
		player->new_x -= player->sin_angle * player->speed;
		player->new_y += player->cos_angle * player->speed;
	}
	if (player->key_right)
	{
		player->new_x += player->sin_angle * player->speed;
		player->new_y -= player->cos_angle * player->speed;
	}
}
