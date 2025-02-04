#include "../Headers/cub3d.h"

void	start_game(t_scene	*img)
{
	init_game(img);
	mlx_hook(img->win_ptr, 2, 1L<<0, key_pres, &img->player);
	mlx_hook(img->win_ptr, 3, 1L<<1, key_release, &img->player);
	mlx_loop_hook(img->mlx_ptr, draw_loop, img);
	mlx_loop(img->mlx_ptr);
}

void	init_game(t_scene *img)
{
	// img->map = get_map();
	// int i=0;
	// while (img->map[i])
	// {
	// 	printf("%s\n", img->map[i]);
	// 	i++;
	// }
	
	// get_map_dimensions(img);
	init_player(&img->player);
	img->mlx_ptr = mlx_init();
	img->win_ptr = mlx_new_window(img->mlx_ptr, WIDTH, HEIGHT, "test");
	img->img = mlx_new_image(img->mlx_ptr, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	// mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img, 0, 0);
}

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	player->left_rotate = false;
	player->right_rotate = false;

	player->speed_rotate = false;
	player->speed = 0.5;
}