/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-ait-bo <a-ait-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:13:12 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/02/06 12:38:22 by a-ait-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	is_wall(t_scene *img, float x, float y)
{
	char	**map;
	int		map_x;
	int		map_y;

	map = img->map;
	map_y = (int)(y / BLOCK);
	map_x = (int)(x / BLOCK);
	if (!map || map_y < 0 || map_x < 0 || \
		map_y >= img->map_height || map_x >= img->map_width)
		return (1);
	return (map[map_y][map_x] == '1');
}

void	clear_image(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0);
			x++;
		}
		y++;
	}
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

void	get_start_x(t_data *data, t_player *player, t_mlx *mlx, t_scene *scene)
{
	float	fr;
	float	start_x;
	int		i;

	i = 0;
	start_x = player->angle - PI / 6;
	fr = PI / 3 / WIDTH;
	while (i < WIDTH)
	{
		get_wall_height(data, start_x, i);
		start_x += fr;
		i++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	dst = data->mlx->addr + (y * data->scene->line_length + x * \
	(data->scene->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
