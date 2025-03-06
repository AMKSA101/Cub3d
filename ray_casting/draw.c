/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:05 by a-ait-bo          #+#    #+#             */
/*   Updated: 2025/03/06 12:47:17 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	key_pres(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_up = true;
	if (keycode == S)
		data->player->key_down = true;
	if (keycode == A)
		data->player->key_left = true;
	if (keycode == D)
		data->player->key_right = true;
	if (keycode == LEFT)
		data->player->left_rotate = true;
	if (keycode == RIGHT)
		data->player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_up = false;
	if (keycode == S)
		data->player->key_down = false;
	if (keycode == A)
		data->player->key_left = false;
	if (keycode == D)
		data->player->key_right = false;
	if (keycode == LEFT)
		data->player->left_rotate = false;
	if (keycode == RIGHT)
		data->player->right_rotate = false;
	return (0);
}

void	move_player(t_scene *img, t_player *player)
{
	float	angle_speed;

	angle_speed = 0.01;
	player->speed = 1;
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle += angle_speed;
	if (player->right_rotate)
		player->angle -= angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	player->new_x = player->x;
	player->new_y = player->y;
	direction_of_player(img, player);
	if (!is_wall(img, player->new_x, player->new_y))
	{
		player->x = player->new_x;
		player->y = player->new_y;
	}
}

void	direction_of_player(t_scene *img, t_player *player)
{
	if (player->key_up)
	{
		player->new_x -= player->cos_angle * player->speed;
		player->new_y -= player->sin_angle * player->speed;
	}
	if (player->key_down)
	{
		player->new_x += player->cos_angle * player->speed;
		player->new_y += player->sin_angle * player->speed;
	}
	if (player->key_left)
	{
		player->new_x -= player->sin_angle * player->speed;
		player->new_y += player->cos_angle * player->speed;
	}
	if (player->key_right)
	{
		player->new_x += player->sin_angle * player->speed;
		player->new_y -= player->cos_angle * player->speed;
	}
}

void	init_game(t_data *data)
{
	t_scene	*img;
	t_mlx	*mlx;

	mlx = data->mlx;
	img = data->scene;
	init_player_position(data->player, data->scene);
	init_player(data->player, data->scene);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "test");
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &img->bits_per_pixel, \
									&img->line_length, &img->endian);
}

void	init_player_position(t_player *player, t_scene *img)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = img->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S')
			{
				player->x = j * BLOCK;
				player->y = i * BLOCK;
			}
			j++;
		}
		i++;
	}
}

void	init_player(t_player *player, t_scene *img)
{
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->speed_rotate = false;
	player->speed = 0.2;
}

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

void	get_wall_height(t_data *data, float start_x, int i)
{
	t_ray	*ray;
	float	cos_angle;
	float	sin_angle;
	float	step_size = 0.01; // Adjusted step size for clarity

	ray = data->ray;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray->ray_x = data->player->x;
	ray->ray_y = data->player->y;
	ray->wall = NONE; // Initialize wall
	// Raycasting loop with more detailed hit detection:
	while (ray->wall == NONE)
	{
		ray->ray_x -= cos_angle * step_size;
		ray->ray_y -= sin_angle * step_size;
		if (is_wall(data->scene, ray->ray_x, ray->ray_y))
		{
			// Determine which wall was hit based on 'side' from the DDA algorithm.
			// Assuming 'side' is 0 for North/South and 1 for East/West
			// You'll need to correctly implement DDA to determine the `side` variable during the raycasting loop
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
		// Add a safety check to prevent infinite loops if is_wall is broken
		if (fabs(ray->ray_x - data->player->x) > 100 || fabs(ray->ray_y - data->player->y) > 100) {
			ray->wall = NONE;
			break;
		}
	}
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
}

void    draw_wall(t_data *data, float start_x, int i)
{
	int         y;
	int         color;
	t_texture   *textures = data->texture;
	int         tex_width, tex_height;
	char        *texture_addr;
	int         bits_per_pixel, line_length, endian;

	y = 0;
	void *texture = NULL;
	double wall_x;
	double tex_x;
	switch (data->ray->wall)
	{
		case NORTH:
			texture = textures->north;
			tex_width = textures->north_width;
			tex_height = textures->north_height;
			wall_x = data->ray->ray_x;
			break;
		case SOUTH:
			texture = textures->south;
			tex_width = textures->south_width;
			tex_height = textures->south_height;
			wall_x = data->ray->ray_x;
			break;
		case EAST:
			texture = textures->east;
			tex_width = textures->east_width;
			tex_height = textures->east_height;
			wall_x = data->ray->ray_y;
			break;
		case WEST:
			texture = textures->west;
			tex_width = textures->west_width;
			tex_height = textures->west_height;
			wall_x = data->ray->ray_y;
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

	while (y < data->ray->start_y)
	{
		my_mlx_pixel_put(data, i, y, data->scene->ceiling_color);
		y++;
	}
	y = data->ray->start_y;
	while (y < data->ray->end_y)
	{
		double tex_y = (double)(y - data->ray->start_y) / (data->ray->end_y - data->ray->start_y);

		tex_x = fmod(wall_x, BLOCK) / BLOCK;

		if (tex_x < 0)
			tex_x += 1; // Ensure tex_x is within [0, 1)

		int tex_x_int = (int)(tex_x * tex_width);
		int tex_y_int = (int)(tex_y * tex_height);

		char *dst = texture_addr + (tex_y_int * line_length + tex_x_int * (bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		my_mlx_pixel_put(data, i, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data, i, y, data->scene->floor_color);
		y++;
	}
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
