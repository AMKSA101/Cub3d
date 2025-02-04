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

// char	**get_map()
// {  
// 	char **map = malloc(sizeof(char *) * 11);
// 	map[0] = strdup("111111111111111111111"); //fill the map
// 	map[1] = strdup("100000000000000100001");
// 	map[2] = strdup("100100000100000000001");
// 	map[3] = strdup("100100000000000010001");
// 	map[4] = strdup("100100000000000000001");
// 	map[5] = strdup("10010000000000P00001");
// 	map[6] = strdup("100100000000000000001");
// 	map[7] = strdup("100100000000010000001");
// 	map[8] = strdup("111111111111111111111");
// 	map[9] = NULL;
// 	return (map);
// }

void	get_map_dimensions(t_scene *img)
{
	int i;

	i = 0;
	img->map_width = ft_strlen(img->map[i]);
	while (img->map[i])
	{
			// printf("%s\n", img->map[i]);
		int	j = 0;
		while (img->map[i][j])
		{
			if (img->map[i][j] == 'P')
			{
				img->player.x = j * BLOCK;
				img->player.y = i * BLOCK;
			}
			j++;
		}
		i++;
	}
	img->map_height = i;
}

int is_wall(t_scene *img, float x, float y)
{
	int map_x = (int)(x / BLOCK);
	int map_y = (int)(y / BLOCK);

	if (map_x < 0 || map_x >= WIDTH || 
		map_y < 0 || map_y >= HEIGHT)
		return 1;
	
	return img->map[map_y][map_x] == '1';
}

void	clear_image(t_scene *img)
{
	int y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(img, x, y, 0);
			x++;
		}
		y++;
	}

}

bool touch(float px, float py, t_scene *img)
{
	int x = (int)(px / BLOCK);
	int y = (int)(py / BLOCK);

	if (x < 0 || x >= (int)ft_strlen(img->map[0]) || 
		y < 0 || y >= 9)
		return true;
	
	return (img->map[y][x] == '1');
}

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}
