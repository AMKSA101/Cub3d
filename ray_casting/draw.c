/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:05 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/03/08 12:40:50 by abamksa          ###   ########.fr       */
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

void	get_wall_height(t_data *data, float start_x, int i)
{
	t_ray	*ray;
	float	cos_angle;
	float	sin_angle;
	float	step_size = 0.1;

	ray = data->ray;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray->ray_x = data->player->x;
	ray->ray_y = data->player->y;
	ray->wall = NONE;

	while (ray->wall == NONE)
	{
		ray->ray_x -= cos_angle * step_size;
		ray->ray_y -= sin_angle * step_size;

		if (is_wall(data->scene, ray->ray_x, ray->ray_y))
		{
			if (fabs(ray->ray_x - data->player->x) > fabs(ray->ray_y - data->player->y)) {
				if (cos_angle > 0) {
					ray->wall = WEST;
				} else {
					ray->wall = EAST;
				}
				ray->wall_x = ray->ray_y;
			}
			else {
					if (sin_angle > 0) {
					ray->wall = NORTH;
				} else {
					ray->wall = SOUTH;
				}
					ray->wall_x = ray->ray_x;
			}
			ray->hit_x = (int)ray->ray_x;
			ray->hit_y = (int)ray->ray_y;
			break;
		}

		if (fabs(ray->ray_x - data->player->x) > 1000 || fabs(ray->ray_y - data->player->y) > 1000) {
			ray->wall = NONE;
			break;
		}
	}
	ray->dist = distance(ray->ray_x - data->player->x, ray->ray_y - data->player->y);
	ray->dist = ray->dist * cos(data->player->angle - start_x);
	ray->height = (BLOCK / ray->dist) * (HEIGHT / 2);
	ray->start_y = (HEIGHT - ray->height) / 2;
	ray->end_y = ray->height + ray->start_y;

	// if (ray->start_y < 0)
	// 	ray->start_y = 0;
	// if (ray->end_y > HEIGHT)
	// 	ray->end_y = HEIGHT;
	draw_wall(data, start_x, i);
}

void	draw_wall(t_data *data, float start_x, int i)
{
	t_ray		*ray;
	t_texture	*textures;
	void		*texture;
	int			tex_width, tex_height;
	char		*texture_addr;
	int			bits_per_pixel, line_length, endian;
	int			y, color;
	float		wall_hit, tex_x;
	int			tex_x_int, tex_y_int;

	ray = data->ray;
	textures = data->texture;
	texture = NULL;

	switch (ray->wall)
	{
	case NORTH:
		texture = textures->north;
		tex_width = textures->north_width;
		tex_height = textures->north_height;
		break;
	case SOUTH:
		texture = textures->south;
		tex_width = textures->south_width;
		tex_height = textures->south_height;
		break;
	case EAST:
		texture = textures->east;
		tex_width = textures->east_width;
		tex_height = textures->east_height;
		break;
	case WEST:
		texture = textures->west;
		tex_width = textures->west_width;
		tex_height = textures->west_height;
		break;
	default:
		tex_width = 0;
		tex_height = 0;
	}
	if (texture == NULL)
	{
		while (y < data->ray->start_y)
		{
			my_mlx_pixel_put(data, i, y, data->scene->ceiling_color);
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
			my_mlx_pixel_put(data, i, y, data->scene->floor_color);
			y++;
		}
		return;
	}

	texture_addr = mlx_get_data_addr(texture, &bits_per_pixel, &line_length, &endian);

	// Determine where the ray hit the wall to calculate texture X coordinate
	if (ray->wall == NORTH || ray->wall == SOUTH)
	{
		wall_hit = ray->ray_x / (float)BLOCK;
		if (sin(start_x) <= 0)
			ray->side = 0;  // Facing up
		else
			ray->side = 1;  // Facing down
	}
	else
	{
		wall_hit = ray->ray_y / (float)BLOCK;
		if (cos(start_x) <= 0)
			ray->side = 2;  // Facing left
		else
			ray->side = 3;  // Facing right
	}

	wall_hit -= floor(wall_hit);  // Get fractional part
	tex_x = wall_hit * tex_width;
	tex_x_int = (int)tex_x;
	if (tex_x_int < 0)
		tex_x_int = 0;
	else if (tex_x_int >= tex_width)
		tex_x_int = tex_width - 1;

	y = 0;
	while (y < ray->start_y)
	{
		my_mlx_pixel_put(data, i, y, data->scene->ceiling_color);
		y++;
	}
	y = ray->start_y;
	while (y < ray->end_y)
	{
		float tex_y = (float)(y - ray->start_y) / (float)(ray->end_y - ray->start_y);
		tex_y_int = (int)(tex_y * tex_height);
		if (tex_y_int < 0) tex_y_int = 0;
		else if (tex_y_int >= tex_height) tex_y_int = tex_height - 1;

		char *dst = texture_addr + (tex_y_int * line_length + tex_x_int * (bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		my_mlx_pixel_put(data, i, y, color);
		y++;
	}

	y = ray->end_y;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data, i, y, data->scene->floor_color);
		y++;
	}
}

