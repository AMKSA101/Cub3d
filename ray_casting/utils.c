/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:13:12 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/04/04 11:18:04 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	check_wall(t_scene *img,	char    **map, float x, float y)
{
	float	offset;
	int		map_x;
	int		map_y;

	map_y = (int)(y / BLOCK);
	map_x = (int)(x / BLOCK);
	// offset = 14;
	offset = 0.1;
	map_x = (int)((x + offset) / BLOCK);
	if (map_x < img->map_width && map[map_y][map_x] == '1')
		if (x + offset >= map_x * BLOCK && x + offset < (map_x + 1) * BLOCK)
			return (1);
	map_x = (int)((x - offset) / BLOCK);
	if (map_x >= 0 && map[map_y][map_x] == '1')
		if (x - offset >= map_x * BLOCK && x - offset < (map_x + 1) * BLOCK)
			return (1);
	map_x = (int)(x / BLOCK);
	map_y = (int)((y - offset) / BLOCK);
	if (map_y >= 0 && map[map_y][map_x] == '1')
		if (y - offset >= map_y * BLOCK && y - offset < (map_y + 1) * BLOCK)
			return (1);
	map_y = (int)((y + offset) / BLOCK);
	if (map_y < img->map_height && map[map_y][map_x] == '1')
		if (y + offset >= map_y * BLOCK && y + offset < (map_y + 1) * BLOCK)
			return (1);
	return (0);
}

int is_wall(t_scene *img, float x, float y)
{
	char	**map;
	int		map_x;
	int		map_y;

	map = img->map;
	map_y = (int)(y / BLOCK);
	map_x = (int)(x / BLOCK);
	if (!map || map_y < 0 || map_x < 0 || 
		map_y >= img->map_height || map_x >= img->map_width)
		return (1);
	if (map[map_y][map_x] == '1')
		return (1);
	return (check_wall(img, map, x, y));
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

	fr = PI / 3.0f / (float)WIDTH;
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
