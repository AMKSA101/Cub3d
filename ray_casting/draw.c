/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:05 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/04/12 18:46:17 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	draw_loop(t_data *data)
{
	t_player	*player;
	t_mlx		*mlx;
	t_scene		*scene;
	int			size_color[2];

	size_color[0] = 5;
	size_color[1] = 0x0000FF;
	player = data->player;
	mlx = data->mlx;
	scene = data->scene;
	move_player(data->scene, data->player);
	clear_image(data);
	get_start_x(data, player, mlx, scene);
	draw_map(data);
	draw_pixel(data, player->x / BLOCK * 10,
		player->y / BLOCK * 10, size_color);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	return (0);
}

void	draw_pixel(t_data *data, int x, int y, int *size_color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size_color[0])
	{
		j = 0;
		while (j < size_color[0])
		{
			my_mlx_pixel_put(data, x + i, y + j, size_color[1]);
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
	int		size_color[2];

	size_color[0] = 10;
	size_color[1] = 0x781FA1;
	y = 0;
	map = data->scene->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				draw_pixel(data, x * 10, y * 10, size_color);
			}
			x++;
		}
		y++;
	}
}

void	get_wall_height(t_data *data, float start_x, int i)
{
	t_ray	*ray;

	ray = data->ray;
	data->ray->ray_dir_x = cos(start_x);
	data->ray->ray_dir_y = sin(start_x);
	data->scene->map_x = (int)(data->player->x / BLOCK);
	data->scene->map_y = (int)(data->player->y / BLOCK);
	if (!data->ray->ray_dir_x)
		data->ray->delta_dist_x = 1e30;
	else
		data->ray->delta_dist_x = fabs(1.0 / data->ray->ray_dir_x);
	if (!data->ray->ray_dir_y)
		data->ray->delta_dist_y = 1e30;
	else
		data->ray->delta_dist_y = fabs(1.0 / data->ray->ray_dir_y);
	get_side_dist(data);
	get_side(data);
	get_wall_height_tow(data, ray, start_x, i);
}

void	draw_wall(t_data *data, float start_x, int i)
{
	int	y;
	int	color;

	data->texture->texture_ = NULL;
	get_direction(data);
	check_tex(data, i);
	data->texture->texture_addr = mlx_get_data_addr(data->texture->texture_,
			&data->texture->bits_per_pixel, &data->texture->line_length,
			&data->texture->endian);
	y = 0;
	while (y < data->ray->start_y)
	{
		my_mlx_pixel_put(data, i, y, data->scene->ceiling_color);
		y++;
	}
	draw_tex(data, i, 0, 0);
	y = data->ray->end_y;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data, i, y, data->scene->floor_color);
		y++;
	}
}
