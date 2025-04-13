/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:00:34 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/13 10:00:38 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	debug_ray_info(t_data *data, int i)
{
	t_ray	*ray;
	char	debug_str[256];

	ray = data->ray;
	if (i == WIDTH / 2)
	{
		sprintf(debug_str, "Ray %d: Wall=%d, Side=%d, WallX=%.2f, Dist=%.2f",
			i, ray->wall, ray->side, ray->wall_x, ray->dist);
		mlx_string_put(data->mlx->mlx_ptr, data->mlx->win_ptr,
			10, 20, 0xFFFFFF, debug_str);
	}
}

void	check_tex(t_data *data, int i)
{
	int	y;

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
		return ;
	}
}

void	tex_x_y(double *tex_x, double *tex_y, int y, t_data *data)
{
	*tex_y = (double)(y - data->ray->start_y)
		/ (double)(data->ray->end_y - data->ray->start_y);
	*tex_x = data->ray->wall_x;
	if (data->ray->wall == WEST || data->ray->wall == SOUTH)
		*tex_x = 1.0 - *tex_x;
	*tex_x = fmax(0.0, fmin(0.999, *tex_x));
	*tex_y = fmax(0.0, fmin(0.999, *tex_y));
}

void	check_x_y(int *tex_x, int *tex_y)
{
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_y < 0)
		*tex_y = 0;
}

void	draw_tex(t_data *data, int i, double tex_x, double tex_y)
{
	int		y;
	int		color;
	char	*dst;
	int		tex_x_int;
	int		tex_y_int;

	y = data->ray->start_y;
	while (y < data->ray->end_y)
	{
		tex_x_y(&tex_x, &tex_y, y, data);
		tex_x_int = (int)(tex_x * data->texture->tex_width);
		tex_y_int = (int)(tex_y * data->texture->tex_height);
		check_x_y(&tex_x_int, &tex_y_int);
		if (tex_x_int >= data->texture->tex_width)
			tex_x_int = data->texture->tex_width - 1;
		if (tex_y_int >= data->texture->tex_height)
			tex_y_int = data->texture->tex_height - 1;
		dst = data->texture->texture_addr + (tex_y_int
				* data->texture->line_length + tex_x_int
				* (data->texture->bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		my_mlx_pixel_put(data, i, y, color);
		y++;
	}
}
