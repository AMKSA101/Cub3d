/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:05:55 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/13 10:06:13 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	get_side_dist(t_data *data)
{
	if (data->ray->ray_dir_x < 0)
	{
		data->ray->step_x = -1;
		data->ray->side_dist_x = (data->player->x
				/ BLOCK - data->scene->map_x) * data->ray->delta_dist_x;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->side_dist_x = (data->scene->map_x + 1.0
				- data->player->x / BLOCK) * data->ray->delta_dist_x;
	}
	if (data->ray->ray_dir_y < 0)
	{
		data->ray->step_y = -1;
		data->ray->side_dist_y = (data->player->y
				/ BLOCK - data->scene->map_y) * data->ray->delta_dist_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->side_dist_y = (data->scene->map_y + 1.0 - data->player->y
				/ BLOCK) * data->ray->delta_dist_y;
	}
}

void	get_side(t_data *data)
{
	int	hit;

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
		if (data->scene->map_x < 0 || data->scene->map_y < 0
			|| data->scene->map_x >= data->scene->map_width
			|| data->scene->map_y >= data->scene->map_height
			|| data->scene->map[data->scene->map_y][data->scene->map_x] == '1')
			hit = 1;
	}
}

void	get_wall_height_th(t_data *data, t_ray *ray, float start_x, int i)
{
	char	debug_str[256];

	ray->hit_x = data->scene->map_x;
	ray->hit_y = data->scene->map_y;
	ray->side = data->scene->side;
	ray->dist = data->ray->perp_wall_dist * BLOCK;
	ray->dist = ray->dist * cos(data->player->angle - start_x);
	ray->height = (BLOCK / ray->dist) * (HEIGHT / 2);
	ray->start_y = (HEIGHT - ray->height) / 2;
	ray->end_y = ray->height + ray->start_y;
	draw_wall(data, start_x, i);
	if (i == WIDTH / 2)
	{
		sprintf(debug_str, "Hit: %d,%d Wall:%d Side:%d WX:%.2f",
			ray->hit_x, ray->hit_y, ray->wall, ray->side, ray->wall_x);
		mlx_string_put(data->mlx->mlx_ptr, data->mlx->win_ptr,
			10, 20, 0xFFFFFF, debug_str);
	}
}

void	get_wall_height_tow(t_data *data, t_ray *ray, float start_x, int i)
{
	if (data->scene->side == 0)
		data->ray->perp_wall_dist = (data->ray->side_dist_x
				- data->ray->delta_dist_x);
	else
		data->ray->perp_wall_dist = (data->ray->side_dist_y
				- data->ray->delta_dist_y);
	if (data->scene->side == 0)
	{
		if (data->ray->step_x > 0)
			ray->wall = WEST;
		else
			ray->wall = EAST;
		ray->wall_x = data->player->y / BLOCK + data->ray->perp_wall_dist
			* data->ray->ray_dir_y;
		ray->wall_x = fmod(ray->wall_x, 1.0);
	}
	else
		step_y_set(data, ray);
	if (ray->wall_x < 0)
		ray->wall_x += 1.0;
	get_wall_height_th(data, ray, start_x, i);
}

int	get_direction(t_data *data)
{
	if (data->ray->wall == NORTH)
		return (north_south(data, 1));
	else if (data->ray->wall == SOUTH)
		return (north_south(data, 2));
	else if (data->ray->wall == EAST)
		return (est_west(data, 3));
	else if (data->ray->wall == WEST)
		return (est_west(data, 4));
	data->texture->tex_width = 0;
	data->texture->tex_height = 0;
	return (0);
}
