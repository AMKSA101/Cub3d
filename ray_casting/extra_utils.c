/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 09:48:18 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/13 09:48:23 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
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
	return (0);
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
	return (0);
}

void	step_y_set(t_data *data, t_ray *ray)
{
	if (data->ray->step_y > 0)
		ray->wall = NORTH;
	else
		ray->wall = SOUTH;
	ray->wall_x = data->player->x / BLOCK + data->ray->perp_wall_dist
		* data->ray->ray_dir_x;
	ray->wall_x = fmod(ray->wall_x, 1.0);
}
