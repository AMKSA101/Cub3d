#include "../Headers/cub3d.h"

int	draw_loop(t_scene *img)
{
	t_player *player = &img->player;

	move_player(img, player);
	// draw_map(img);
	// draw_pixel(img, player->x, player->y, 10, 0x00FF0000);
	clear_image(img);

	float fr = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_wall(img, player, start_x, i);
		start_x += fr;
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img, 0, 0);
	return 0;
}

void draw_wall(t_scene *img, t_player *player, float start_x, int i)
{
	float ray_x = player->x;
	float ray_y = player->y;
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);

	while (!touch(ray_x, ray_y, img))
	{
		// my_mlx_pixel_put(img, ray_x, ray_y, 0x0000FF);
		ray_x -= cos_angle*player->speed;
		ray_y -= sin_angle*player->speed;
	}
	// // printf("%f\n", player->speed);
	float dist = distance(ray_x - player->x, ray_y - player->y);
	if (dist < player->speed) dist = player->speed;
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
		my_mlx_pixel_put(img, i, y, 0x87CEEB);
		y++;
	}
	y = start_y; 
	while (y < end_y)
	{
			my_mlx_pixel_put(img, i, y, 0x818181);
		y++;
	}

	y = end_y;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(img, i, y, 0x3A3A3A);
		y++;
	}
	
}

void	my_mlx_pixel_put(t_scene *img, int x, int y, int color)
{
	char	*dst;

	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_pixel(t_scene *img, int x, int y, int size, int color)
{
    int i = 0;
	while (i++ < size)
		my_mlx_pixel_put(img, x + i, y, color);
    i = 0;
	while (i++ < size)
		my_mlx_pixel_put(img, x, y + i, color);
    i = 0;
	while (i++ < size)
		my_mlx_pixel_put(img, x + size, y + i, color);
    i = 0;	
	while (i++ < size)
		my_mlx_pixel_put(img, x + i, y + size, color);
	
}


void	draw_map(t_scene *img)
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
			// if (map[y][x] == 'P')
			// 	draw_pixel(img, x*10, y*10, 10, 0x00FF0000);
			if (map[y][x] == 'D')
				draw_pixel(img, x*BLOCK, y*BLOCK, 10, 0x781fa1);
			if (map[y][x] == '1')
			{
				draw_pixel(img, x*BLOCK, y*BLOCK, 10, 0xff42b5);
				// printf("%d  %d\n", x, y);
			}
            x++;
		}
        y++;
    }

}