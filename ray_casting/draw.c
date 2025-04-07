/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:05 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/04/07 10:02:48 by abamksa          ###   ########.fr       */
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
	float	ray_dir_x, ray_dir_y;
	int		map_x, map_y;
	double	side_dist_x, side_dist_y;
	double	delta_dist_x, delta_dist_y;
	int		step_x, step_y;
	int		hit = 0;
	int		side;

	ray = data->ray;
	ray_dir_x = cos(start_x);
	ray_dir_y = sin(start_x);
	
	// Starting position
	map_x = (int)(data->player->x / BLOCK);
	map_y = (int)(data->player->y / BLOCK);
	
	// Calculate delta distances
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
	
	// Calculate step and initial side_dist
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (data->player->x / BLOCK - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - data->player->x / BLOCK) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (data->player->y / BLOCK - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - data->player->y / BLOCK) * delta_dist_y;
	}
	
	// Perform DDA
	while (hit == 0)
	{
		// Jump to next map square
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0; // X side hit
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; // Y side hit
		}
		
		// Check if ray has hit a wall
		if (map_x < 0 || map_y < 0 || 
			map_x >= data->scene->map_width || 
			map_y >= data->scene->map_height ||
			data->scene->map[map_y][map_x] == '1')
			hit = 1;
	}
	
	// Calculate distance to the wall
	double perp_wall_dist;
	if (side == 0)
		perp_wall_dist = (side_dist_x - delta_dist_x);
	else
		perp_wall_dist = (side_dist_y - delta_dist_y);
	
	// Calculate wall face and wall_x (texture coordinate)
	if (side == 0) // X side
	{
		ray->wall = (step_x > 0) ? WEST : EAST;
		// Calculate exact hit position on the wall
		ray->wall_x = data->player->y / BLOCK + perp_wall_dist * ray_dir_y;
		ray->wall_x = fmod(ray->wall_x, 1.0);
	}
	else // Y side
	{
		ray->wall = (step_y > 0) ? NORTH : SOUTH;
		// Calculate exact hit position on the wall
		ray->wall_x = data->player->x / BLOCK + perp_wall_dist * ray_dir_x;
		ray->wall_x = fmod(ray->wall_x, 1.0);
	}
	
	// Ensure wall_x is positive
	if (ray->wall_x < 0)
		ray->wall_x += 1.0;
	
	// Save hit position for debugging
	ray->hit_x = map_x;
	ray->hit_y = map_y;
	ray->side = side;
	
	// Calculate wall height
	ray->dist = perp_wall_dist * BLOCK;
	ray->height = (BLOCK / ray->dist) * (HEIGHT / 2);
	ray->start_y = (HEIGHT - ray->height) / 2;
	ray->end_y = ray->height + ray->start_y;
	
	// Clamp values
	if (ray->start_y < 0)
		ray->start_y = 0;
	if (ray->end_y > HEIGHT)
		ray->end_y = HEIGHT;
	
	// Draw the wall
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
		// Calculate texture Y coordinate
		double tex_y = (double)(y - data->ray->start_y) / (double)(data->ray->end_y - data->ray->start_y);
		
		// Get texture X from ray wall_x (already normalized 0-1)
		double tex_x = data->ray->wall_x;
		
		// Flip textures if needed based on wall orientation
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
