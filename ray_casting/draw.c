/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-ait-bo <a-ait-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:05 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/02/06 12:41:52 by a-ait-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	draw_loop(t_data *data)
{
	t_player	*player;
	t_mlx		*mlx;
	t_scene		*scene;

	player = data->player;
	mlx = data->mlx;
	scene = data->scene;
	move_player(data->scene, data->player);
	clear_image(data);
	get_start_x(data, player, mlx, scene);
	draw_map(data);
	draw_pixel(data, player->x / BLOCK * 10,
		player->y / BLOCK * 10, 5, 0x0000FF);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	return (0);
}

void	get_wall_height(t_data *data, float start_x, int i)
{
	t_ray	*ray;
	float	cos_angle;
	float	sin_angle;

	ray = data->ray;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray->ray_x = data->player->x;
	ray->ray_y = data->player->y;
	while (!is_wall(data->scene, ray->ray_x, ray->ray_y))
	{
		ray->ray_x -= cos_angle * 0.05;
		ray->ray_y -= sin_angle * 0.05;
	}
	ray->dist = distance(ray->ray_x - data->player->x,
			ray->ray_y - data->player->y);
	ray->dist = ray->dist * cos(data->player->angle - start_x);
	ray->height = (BLOCK / ray->dist) * (HEIGHT / 2);
	ray->start_y = (HEIGHT - ray->height) / 2;
	ray->end_y = ray->height + ray->start_y;
	if (ray->start_y < 0)
		ray->start_y = 0;
	if (ray->end_y > HEIGHT)
		ray->end_y = HEIGHT;
	draw_wall(data, start_x, i);
}

void	draw_wall(t_data *data, float start_x, int i)
{
	int	y;

	y = 0;
	while (y < data->ray->start_y)
	{
		my_mlx_pixel_put(data, i, y, 0x87CEEB);
		y++;
	}
	y = data->ray->start_y;
	while (y < data->ray->end_y)
	{
		my_mlx_pixel_put(data, i, y, 0x818181);
		y++;
	}
	y = data->ray->end_y;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data, i, y, 0x3A3A3A);
		y++;
	}
}

void	draw_pixel(t_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	char	**map;
	int		y;
	int		x;

	y = 0;
	map = data->scene->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				draw_pixel(data, x * 10, y * 10, 10, 0x781FA1);
			}
			x++;
		}
		y++;
	}
}
