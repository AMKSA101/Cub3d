/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:36:22 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/04/14 12:46:44 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	free_mlx(t_data *data)
{
	if (data->mlx)
	{
		if (data->mlx->img)
			mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img);
		if (data->mlx->win_ptr)
			mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
		if (data->mlx->mlx_ptr)
		{
			mlx_destroy_display(data->mlx->mlx_ptr);
			free(data->mlx->mlx_ptr);
		}
	}
}

int	destroynotify(t_data *data)
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
		data->texture = NULL;
	}
	free_scene(data->scene);
	free_mlx(data);
	exit(0);
}

int	key_pres(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_down = true;
	if (keycode == S)
		data->player->key_up = true;
	if (keycode == D)
		data->player->key_left = true;
	if (keycode == A)
		data->player->key_right = true;
	if (keycode == LEFT)
		data->player->left_rotate = true;
	if (keycode == RIGHT)
		data->player->right_rotate = true;
	if (keycode == 65307)
		destroynotify(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_down = false;
	if (keycode == S)
		data->player->key_up = false;
	if (keycode == D)
		data->player->key_left = false;
	if (keycode == A)
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
