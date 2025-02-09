/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-ait-bo <a-ait-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:36:22 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/02/06 11:37:58 by a-ait-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	key_pres(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_up = true;
	if (keycode == S)
		data->player->key_down = true;
	if (keycode == A)
		data->player->key_left = true;
	if (keycode == D)
		data->player->key_right = true;
	if (keycode == LEFT)
		data->player->left_rotate = true;
	if (keycode == RIGHT)
		data->player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_up = false;
	if (keycode == S)
		data->player->key_down = false;
	if (keycode == A)
		data->player->key_left = false;
	if (keycode == D)
		data->player->key_right = false;
	if (keycode == LEFT)
		data->player->left_rotate = false;
	if (keycode == RIGHT)
		data->player->right_rotate = false;
	return (0);
}

void	move_player(t_scene *img, t_player *player)
{
	float	angle_speed;

	angle_speed = 0.01;
	player->speed = 1;
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle += angle_speed;
	if (player->right_rotate)
		player->angle -= angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	player->new_x = player->x;
	player->new_y = player->y;
	direction_of_player(img, player);
	if (!is_wall(img, player->new_x, player->new_y))
	{
		player->x = player->new_x;
		player->y = player->new_y;
	}
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
