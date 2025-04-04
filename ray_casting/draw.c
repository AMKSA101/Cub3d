/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:05 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/04/04 11:23:57 by abamksa          ###   ########.fr       */
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
	int     map_x, map_y;
	float   exact_x, exact_y;

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

		map_x = (int)(ray->ray_x / BLOCK);
		map_y = (int)(ray->ray_y / BLOCK);

		if (map_x < 0 || map_y < 0 || 
			map_x >= data->scene->map_width || 
			map_y >= data->scene->map_height ||
			data->scene->map[map_y][map_x] == '1')
		{
			// Found a wall, determine which face we hit
			// First, get the exact hit position
			exact_x = fmod(ray->ray_x, BLOCK);
			exact_y = fmod(ray->ray_y, BLOCK);
			
			// Normalize to [0, BLOCK] range
			if (exact_x < 0) exact_x += BLOCK;
			if (exact_y < 0) exact_y += BLOCK;
			
			// Determine if hit was on vertical or horizontal wall face
			// We do this by seeing which side of the block we're closest to
			if (exact_x < 1.0) {
				// Hit east face of block
				ray->wall = EAST;
				ray->wall_x = exact_y;
				ray->side = 0;
			}
			else if (exact_x > BLOCK - 1.0) {
				// Hit west face of block
				ray->wall = WEST;
				ray->wall_x = exact_y;
				ray->side = 0;
			}
			else if (exact_y < 1.0) {
				// Hit south face of block
				ray->wall = SOUTH;
				ray->wall_x = exact_x;
				ray->side = 1;
			}
			else if (exact_y > BLOCK - 1.0) {
				// Hit north face of block
				ray->wall = NORTH;
				ray->wall_x = exact_x;
				ray->side = 1;
			}
			else {
				// Inside a block - should not happen with small enough step_size
				// But determine direction based on ray direction
				if (fabs(cos_angle) > fabs(sin_angle)) {
					// Moving mostly horizontally
					ray->wall = (cos_angle > 0) ? WEST : EAST;
					ray->wall_x = exact_y;
					ray->side = 0;
				} else {
					// Moving mostly vertically
					ray->wall = (sin_angle > 0) ? NORTH : SOUTH; 
					ray->wall_x = exact_x;
					ray->side = 1;
				}
			}
			
			// Record hit position
			ray->hit_x = map_x;
			ray->hit_y = map_y;
			break;
		}

		if (fabs(ray->ray_x - data->player->x) > 1000 || fabs(ray->ray_y - data->player->y) > 1000) {
			ray->wall = NONE;
			break;
		}
	}

	// Calculate perpendicular distance to avoid fisheye effect
	ray->dist = distance(ray->ray_x - data->player->x, ray->ray_y - data->player->y);
	ray->dist = ray->dist * cos(data->player->angle - start_x);
	ray->height = (BLOCK / ray->dist) * (HEIGHT / 2);
	ray->start_y = (HEIGHT - ray->height) / 2;
	ray->end_y = ray->height + ray->start_y;

	if (ray->start_y < 0)
		ray->start_y = 0;
	if (ray->end_y > HEIGHT)
		ray->end_y = HEIGHT;
	draw_wall(data, start_x, i);
	
	// Display debug info for center ray
	if (i == WIDTH / 2) {
		char debug_str[256];
		sprintf(debug_str, "Hit: %d,%d Wall:%d Side:%d WX:%.2f", 
				ray->hit_x, ray->hit_y, ray->wall, ray->side, ray->wall_x);
		mlx_string_put(data->mlx->mlx_ptr, data->mlx->win_ptr, 10, 20, 0xFFFFFF, debug_str);
	}
}

void	draw_wall(t_data *data, float start_x, int i)
{
	int y;
	int color;
	t_texture *textures = data->texture;
	int tex_width, tex_height;
	char *texture_addr;
	int bits_per_pixel, line_length, endian;

	y = 0;
	void *texture = NULL;
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

	// Draw ceiling
	y = 0;
	while (y < data->ray->start_y)
	{
		my_mlx_pixel_put(data, i, y, data->scene->ceiling_color);
		y++;
	}

	// Draw textured wall
	y = data->ray->start_y;
	while (y < data->ray->end_y)
	{
		// Calculate texture Y coordinate - this maps the vertical position on wall to texture
		double tex_y = (double)(y - data->ray->start_y) / (double)(data->ray->end_y - data->ray->start_y);
		
		// Calculate texture X coordinate - this uses the hit position on the wall face
		double tex_x = data->ray->wall_x / BLOCK;
		
		// Depending on the wall face, we might need to flip the texture coordinate
		// This ensures textures appear correctly oriented
		if (data->ray->wall == WEST || data->ray->wall == SOUTH)
			tex_x = 1.0 - tex_x;
		
		// Ensure texture coordinates are in valid range
		tex_x = fmax(0.0, fmin(0.999, tex_x));
		tex_y = fmax(0.0, fmin(0.999, tex_y));
		
		// Convert to pixel coordinates in texture
		int tex_x_int = (int)(tex_x * tex_width);
		int tex_y_int = (int)(tex_y * tex_height);
		
		// Safety checks to prevent buffer overflow
		if (tex_x_int < 0) tex_x_int = 0;
		if (tex_y_int < 0) tex_y_int = 0;
		if (tex_x_int >= tex_width) tex_x_int = tex_width - 1;
		if (tex_y_int >= tex_height) tex_y_int = tex_height - 1;
		
		// Get pixel color from texture
		char *dst = texture_addr + (tex_y_int * line_length + tex_x_int * (bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		
		// Draw pixel on screen
		my_mlx_pixel_put(data, i, y, color);
		y++;
	}

	// Draw floor
	y = data->ray->end_y;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data, i, y, data->scene->floor_color);
		y++;
	}
}

// Debug function to show ray information
void debug_ray_info(t_data *data, int i)
{
    t_ray *ray = data->ray;
    char debug_str[256];
    
    // Only print for a specific column to avoid flooding the console
    if (i == WIDTH / 2) {
        sprintf(debug_str, "Ray %d: Wall=%d, Side=%d, WallX=%.2f, Dist=%.2f",
                i, ray->wall, ray->side, ray->wall_x, ray->dist);
        mlx_string_put(data->mlx->mlx_ptr, data->mlx->win_ptr, 10, 20, 0xFFFFFF, debug_str);
    }
}
