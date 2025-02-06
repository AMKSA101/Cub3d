#include "../Headers/cub3d.h"


void	init_game(t_data *data)
{
	t_scene *img = data->scene;
	// img->map = get_map();
	// int i=0;
	// while (img->map[i])
	// {
	// 	printf("%s\n", img->map[i]);
	// 	i++;
	// }
	
	// get_map_dimensions(img);
	t_mlx	*mlx = data->mlx;
	init_player(data->player, data->scene);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "test");
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &img->bits_per_pixel, &img->line_length,
					&img->endian);
	// mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img, 0, 0);
}

void	init_player(t_player *player, t_scene *img)
{
	int i = 0;
	char **map = img->map;
	while (map[i])
	{
		int j = 0;
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