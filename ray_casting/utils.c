/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-ait-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:13:12 by a-ait-bo          #+#    #+#             */
/*   Updated: 2024/04/30 20:13:13 by a-ait-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

// char	**get_map()
// {  
// 	char **map = malloc(sizeof(char *) * 11);
// 	map[0] = strdup("111111111111111111111"); //fill the map
// 	map[1] = strdup("1000000000D0000000001");
// 	map[2] = strdup("1111111111111111111D1");
// 	map[3] = strdup("100000000000D00000001");
// 	map[4] = strdup("1D1111111111111111111");
// 	map[5] = strdup("100000D0000D000P00001");
// 	map[6] = strdup("1D1D1D1D1D1D111111111");
// 	map[7] = strdup("100000000000000000001");
// 	map[8] = strdup("111111111111111111111");
// 	map[9] = NULL;
// 	return (map);
// }

char	**get_map()
{  
	char **map = malloc(sizeof(char *) * 14);
	map[0] = strdup("1111111111111111111111111"); //fill the map
	map[1] = strdup("1000000000110000000000001");
	map[2] = strdup("1011000001110000000000001");
	map[3] = strdup("1111111110110000011100001");
	map[4] = strdup("100S011111111111111111111");
	map[5] = strdup("100100000000000000000000000000001");
	map[6] = strdup("1011111111111111111111111");
	map[7] = strdup("1000000110101011000010001");
	map[8] = strdup("1000000000000000000010001");
	map[9] = strdup("1000000000000000110000001");
	map[10] = strdup("110000011101110111111011");
	map[11] = strdup("111101111110101101111001");
	map[12] = strdup("111111111111111111111111");
	map[13] = NULL;
	return (map);
}

// void	get_map_dimensions(t_data *data, t_scene *img)
// {
// 	int i;

// 	i = 0;
// 	img->map_width = ft_strlen(img->map[i]);
// 	while (img->map[i])
// 	{
// 			// printf("%s\n", img->map[i]);
// 		int	j = 0;
// 		while (img->map[i][j])
// 		{
// 			if (img->map[i][j] == 'P')
// 			{
// 				data->player->x = j * BLOCK;
// 				data->player->y = i * BLOCK;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	img->map_height = i;
// }

int is_wall(t_scene *img, float x, float y)
{
	int map_x = (int)(x / BLOCK);
	int map_y = (int)(y / BLOCK);
	char **map = img->map;

	// printf("%d   %d\n", map_y, map_x);
	if (!map || map_y < 0 || map_x < 0 || 
        map_y >= img->map_height || map_x >= img->map_width)
		return 1;
	return (map[map_y][map_x] == '1');

}

void	clear_image(t_mlx *mlx, t_scene *img)
{
	int y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(mlx, img, x, y, 0);
			x++;
		}
		y++;
	}

}

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}
