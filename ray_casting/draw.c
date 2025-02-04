#include "../Headers/cub3d.h"

int	draw_loop(t_data *data)
{
	t_player *player = data->player;
	t_mlx	*mlx = data->mlx;
	t_scene	*scene = data->scene;
	move_player(data->scene, data->player);
	clear_image(data->mlx, data->scene);

	float fr = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_wall(mlx, scene, player, start_x, i);
		start_x += fr;
		i++;
	}
	draw_map(mlx, scene);
	draw_pixel(mlx, scene, player->x/BLOCK*10, player->y/BLOCK*10, 2, 0x0000FF);
	printf("%p\n", mlx->addr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	return 0;
}


void draw_wall(t_mlx *mlx, t_scene *img, t_player *player, float start_x, int i)
{
	float ray_x = player->x;
	float ray_y = player->y;
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	  float step = 0.05;

	while (!is_wall(img, ray_x, ray_y))
	{
		my_mlx_pixel_put(mlx, img, ray_x/BLOCK*10, ray_y/BLOCK*10, 0x0000FF);
		ray_x -= cos_angle*step;
		ray_y -= sin_angle*step;
	}
	float dist = distance(ray_x - player->x, ray_y - player->y);
	if (dist < player->speed) dist = player->speed;
	dist = dist * cos(player->angle - start_x);
	float height = (BLOCK / dist) * (HEIGHT / 2);
	int start_y = (HEIGHT - height) / 2;
	int end_y = height + start_y;

	if (start_y < 0)
		start_y = 0;
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	
	int y = 0;
	while (y < start_y)
	{
		my_mlx_pixel_put(mlx, img, i, y, 0x87CEEB);
		y++;
	}
	y = start_y; 
	while (y < end_y)
	{
			my_mlx_pixel_put(mlx, img, i, y, 0x818181);
		y++;
	}

	y = end_y;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(mlx, img, i, y, 0x3A3A3A);
		y++;
	}
	
}

void	my_mlx_pixel_put(t_mlx *mlx, t_scene *img, int x, int y, int color)
{
	char	*dst;
	
	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	dst = mlx->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void	draw_pixel(t_mlx *mlx, t_scene *img, int x, int y, int size, int color)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(mlx, img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_mlx *mlx, t_scene *img)
{
	char **map =img->map;
	// int i=0;
	// while (map[i])
	// {
	// 	printf("%s\n", map[i]);
	// 	i++;
	// }
	int y = 0;
	while (map[y])
	{
		int x = 0;
		while (map[y][x])
		{
			// if (map[y][x] == 'S')
			// 	draw_pixel(img, x*BLOCK, y*BLOCK, 5, 0x00FF0000);
			// if (map[y][x] == '0')
			// 	draw_pixel(img,x*10, y*10, 10, 0);
			if (map[y][x] == '1')
			{
				draw_pixel(mlx, img, x*10, y*10, 10, 0x781FA1);
				// printf("%d  %d\n", x, y);
			}
			x++;
		}
		y++;
	}

}