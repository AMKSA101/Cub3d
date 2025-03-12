/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:05 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/03/12 12:16:32 by abamksa          ###   ########.fr       */
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

void get_wall_height(t_data *data, float start_x, int i)
{
	t_ray *ray = data->ray;
	float cos_angle = cosf(start_x);
	float sin_angle = sinf(start_x);

	ray->ray_x = data->player->x;
	ray->ray_y = data->player->y;
	ray->wall = NONE;

	// DDA setup
	int stepX, stepY;
	float sideDistX, sideDistY;
	float deltaDistX = fabsf(1.0f / cos_angle);
	float deltaDistY = fabsf(1.0f / sin_angle);

	if (cos_angle > 0) {
		stepX = 1;
		sideDistX = ((int)(ray->ray_x / BLOCK) + 1) * BLOCK - ray->ray_x;
	} else {
		stepX = -1;
		sideDistX = ray->ray_x - (int)(ray->ray_x / BLOCK) * BLOCK;
	}

	if (sin_angle > 0) {
		stepY = 1;
		sideDistY = ((int)(ray->ray_y / BLOCK) + 1) * BLOCK - ray->ray_y;
	} else {
		stepY = -1;
		sideDistY = ray->ray_y - (int)(ray->ray_y / BLOCK) * BLOCK;
	}

	// DDA loop
	while (ray->wall == NONE) {
		if (sideDistX < sideDistY) {
			sideDistX += deltaDistX;
			ray->ray_x += stepX;
			ray->side = 0; // Vertical hit
		} else {
			sideDistY += deltaDistY;
			ray->ray_y += stepY;
			ray->side = 1; // Horizontal hit
		}

		if (is_wall(data->scene, ray->ray_x, ray->ray_y)) {
			if (ray->side == 0) {
				if (stepX > 0) ray->wall = WEST;
				else ray->wall = EAST;
			} else {
				if (stepY > 0) ray->wall = NORTH;
				else ray->wall = SOUTH;
			}
			break; 
		}
		if (fabs(ray->ray_x - data->player->x) > 1000 || 
			fabs(ray->ray_y - data->player->y) > 1000) {
			ray->wall = NONE; // Maximum ray distance or out of bounds
			break;
		}
	}


	if (ray->side == 0) {
		ray->dist = (ray->ray_x - data->player->x + (1 - stepX) / 2) / cos_angle;
	} else {
		ray->dist = (ray->ray_y - data->player->y + (1 - stepY) / 2) / sin_angle;
	}


	ray->dist *= cosf(data->player->angle - start_x);
	ray->height = (BLOCK / ray->dist) * (HEIGHT / 2);
	ray->start_y = (HEIGHT - ray->height) / 2;
	ray->end_y = ray->height + ray->start_y;
	// 	if (ray->start_y < 0)
	// 		ray->start_y = 0;
	// 	if (ray->end_y > HEIGHT)
	// 		ray->end_y = HEIGHT;
	draw_wall(data, start_x, i);

}

void draw_wall(t_data *data, float start_x, int i)
{
	int y = 0;
	int color;
	t_texture *textures = data->texture;
	int tex_width, tex_height;
	char *texture_addr;
	int bits_per_pixel, line_length, endian;

	void *texture = NULL; // Initialize
	switch (data->ray->wall)
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

	// Ceiling
	while (y < data->ray->start_y) {
		my_mlx_pixel_put(data, i, y, data->scene->ceiling_color);
		y++;
	}

	// Wall
	for (y = data->ray->start_y; y < data->ray->end_y; ++y) {
		double tex_y = (double)(y - data->ray->start_y) * tex_height / (double)(data->ray->end_y - data->ray->start_y);
		int tex_y_int = (int)tex_y;
		if (tex_y_int >= tex_height) {
			tex_y_int = tex_height - 1; // VERY IMPORTANT: Prevents out-of-bounds access
		}


		double wallX;
		if (data->ray->side == 0) {
			wallX = data->player->y + data->ray->dist * sinf(start_x);
		} else {
			wallX = data->player->x + data->ray->dist * cosf(start_x);
		}


		wallX -= floor(wallX);

		int tex_x_int = (int)(wallX * tex_width);


		// VERY IMPORTANT: Bounds checking
		if (tex_x_int < 0) {
			tex_x_int = 0;
		}
		if (tex_x_int >= tex_width) {
			tex_x_int = tex_width - 1;
		}

		char *dst = texture_addr + (tex_y_int * line_length + tex_x_int * (bits_per_pixel / 8));
		color = *(unsigned int *)dst;  // corrected
		my_mlx_pixel_put(data, i, y, color);
	}

	// Floor
	y = data->ray->end_y;  // correct y value for floor rendering
	while (y < HEIGHT) {
		my_mlx_pixel_put(data, i, y, data->scene->floor_color);
		y++;
	}
}
