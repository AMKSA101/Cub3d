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


void get_side_dist(t_data *data)
{
	if (data->ray->ray_dir_x < 0)
	{
		data->ray->step_x = -1;
		data->ray->side_dist_x = (data->player->x / BLOCK - data->scene->map_x) * data->ray->delta_dist_x;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->side_dist_x = (data->scene->map_x + 1.0 - data->player->x / BLOCK) * data->ray->delta_dist_x;
	}
	if (data->ray->ray_dir_y < 0)
	{
		data->ray->step_y = -1;
		data->ray->side_dist_y = (data->player->y / BLOCK - data->scene->map_y) * data->ray->delta_dist_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->side_dist_y = (data->scene->map_y + 1.0 - data->player->y / BLOCK) * data->ray->delta_dist_y;
	}
}

void	get_side(t_data *data)
{
	int	hit;
	// int	data->ray->side;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray->side_dist_x < data->ray->side_dist_y)
		{
			data->ray->side_dist_x += data->ray->delta_dist_x;
			data->scene->map_x += data->ray->step_x;
			data->scene->side = 0;
		}
		else
		{
			data->ray->side_dist_y += data->ray->delta_dist_y;
			data->scene->map_y += data->ray->step_y;
			data->scene->side = 1;
		}
		if (data->scene->map_x < 0 || data->scene->map_y < 0 || 
			data->scene->map_x >= data->scene->map_width || 
			data->scene->map_y >= data->scene->map_height ||
			data->scene->map[data->scene->map_y][data->scene->map_x] == '1')
			hit = 1;
	}
}

void	get_wall_height_th(t_data *data, t_ray *ray, float start_x, int i)
{
	ray->hit_x = data->scene->map_x;
	ray->hit_y = data->scene->map_y;
	ray->side = data->scene->side;
	ray->dist = data->ray->perp_wall_dist * BLOCK;
	ray->dist = ray->dist * cos(data->player->angle - start_x);
	ray->height = (BLOCK / ray->dist) * (HEIGHT / 2);
	ray->start_y = (HEIGHT - ray->height) / 2;
	ray->end_y = ray->height + ray->start_y;

	// if (ray->start_y < 0)
	// 	ray->start_y = 0;
	// if (ray->end_y > HEIGHT)
	// 	ray->end_y = HEIGHT;

	draw_wall(data, start_x, i);
	if (i == WIDTH / 2) {
		char debug_str[256];
		sprintf(debug_str, "Hit: %d,%d Wall:%d Side:%d WX:%.2f", 
				ray->hit_x, ray->hit_y, ray->wall, ray->side, ray->wall_x);
		mlx_string_put(data->mlx->mlx_ptr, data->mlx->win_ptr, 10, 20, 0xFFFFFF, debug_str);
	}
}

void	get_wall_height_tow(t_data *data, t_ray *ray, float start_x, int i)
{
	if (data->scene->side == 0)
		data->ray->perp_wall_dist = (data->ray->side_dist_x - data->ray->delta_dist_x);
	else
		data->ray->perp_wall_dist = (data->ray->side_dist_y - data->ray->delta_dist_y);
	if (data->scene->side == 0) // X side
	{
		ray->wall = (data->ray->step_x > 0) ? WEST : EAST;
		ray->wall_x = data->player->y / BLOCK + data->ray->perp_wall_dist * data->ray->ray_dir_y;
		ray->wall_x = fmod(ray->wall_x, 1.0);
	}
	else // Y side
	{
		ray->wall = (data->ray->step_y > 0) ? NORTH : SOUTH;
		ray->wall_x = data->player->x / BLOCK + data->ray->perp_wall_dist * data->ray->ray_dir_x;
		ray->wall_x = fmod(ray->wall_x, 1.0);
	}
	if (ray->wall_x < 0)
		ray->wall_x += 1.0;
	get_wall_height_th(data, ray, start_x, i);
}

void	get_wall_height(t_data *data, float start_x, int i)
{
	t_ray	*ray;

	ray = data->ray;
	data->ray->ray_dir_x = cos(start_x);
	data->ray->ray_dir_y = sin(start_x);
	data->scene->map_x = (int)(data->player->x / BLOCK);
	data->scene->map_y = (int)(data->player->y / BLOCK);
	data->ray->delta_dist_x = (data->ray->ray_dir_x == 0) ? 1e30 : fabs(1.0 / data->ray->ray_dir_x);
	data->ray->delta_dist_y = (data->ray->ray_dir_y == 0) ? 1e30 : fabs(1.0 / data->ray->ray_dir_y);
	get_side_dist(data);
	get_side(data);
	get_wall_height_tow(data, ray, start_x, i);
}
int	est_west(t_data *data, int i)
{
	if (i == 3)
	{
		data->texture->texture_ = data->texture->east;
		data->texture->tex_width = data->texture->east_width;
		data->texture->tex_height = data->texture->east_height;
		return (1);
	}
	if (i == 4)
	{
		data->texture->texture_ = data->texture->west;
		data->texture->tex_width = data->texture->west_width;
		data->texture->tex_height = data->texture->west_height;
		return (1);
	}
	return 0;
}
int	north_south(t_data *data, int i)
{
	if (i == 1)
	{
		data->texture->texture_ = data->texture->north;
		data->texture->tex_width = data->texture->north_width;
		data->texture->tex_height = data->texture->north_height;
		return (1);
	}
	else if (i == 2)
	{
		data->texture->texture_ = data->texture->south;
		data->texture->tex_width = data->texture->south_width;
		data->texture->tex_height = data->texture->south_height;
		return (1);
	}
	return 0;
}

int get_direction(t_data *data)
{
    if (data->ray->wall == NORTH)
        return north_south(data, 1);
    else if (data->ray->wall == SOUTH)
        return north_south(data, 2);
    else if (data->ray->wall == EAST)
        return est_west(data, 3);
    else if (data->ray->wall == WEST)
        return est_west(data, 4);
    data->texture->tex_width = 0;
    data->texture->tex_height = 0;
    return 0;
}

void	check_tex(t_data *data, int i)
{
	int y;

	y = 0;
	if (data->texture->texture_ == NULL)
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
}

void draw_tex(t_data *data, int i)
{
	int y;
	int color;

	y = data->ray->start_y;
	while (y < data->ray->end_y)
	{
		double tex_y = (double)(y - data->ray->start_y) / (double)(data->ray->end_y - data->ray->start_y);
		double tex_x = data->ray->wall_x;
		if (data->ray->wall == WEST || data->ray->wall == SOUTH)
			tex_x = 1.0 - tex_x;
		tex_x = fmax(0.0, fmin(0.999, tex_x));
		tex_y = fmax(0.0, fmin(0.999, tex_y));
		int tex_x_int = (int)(tex_x * data->texture->tex_width);
		int tex_y_int = (int)(tex_y * data->texture->tex_height);
		if (tex_x_int < 0) tex_x_int = 0;
		if (tex_y_int < 0) tex_y_int = 0;
		if (tex_x_int >= data->texture->tex_width) tex_x_int = data->texture->tex_width - 1;
		if (tex_y_int >= data->texture->tex_height) tex_y_int = data->texture->tex_height - 1;
		char *dst = data->texture->texture_addr + (tex_y_int * data->texture->line_length + 
		tex_x_int * (data->texture->bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		my_mlx_pixel_put(data, i, y, color);
		y++;
	}
}
void	draw_wall(t_data *data, float start_x, int i)
{
	int y;
	int color;

	
	data->texture->texture_ = NULL;
	get_direction(data);
	check_tex(data, i);
	data->texture->texture_addr = mlx_get_data_addr(data->texture->texture_, &data->texture->bits_per_pixel,
	 &data->texture->line_length, &data->texture->endian);
	y = 0;
	while (y < data->ray->start_y)
	{
		my_mlx_pixel_put(data, i, y, data->scene->ceiling_color);
		y++;
	}
	draw_tex(data, i);
	y = data->ray->end_y;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data, i, y, data->scene->floor_color);
		y++;
	}
}

void debug_ray_info(t_data *data, int i)
{
    t_ray *ray;
    char debug_str[256];
    
	ray = data->ray;
    if (i == WIDTH / 2) {
        sprintf(debug_str, "Ray %d: Wall=%d, Side=%d, WallX=%.2f, Dist=%.2f",
                i, ray->wall, ray->side, ray->wall_x, ray->dist);
        mlx_string_put(data->mlx->mlx_ptr, data->mlx->win_ptr, 10, 20, 0xFFFFFF, debug_str);
    }
}
