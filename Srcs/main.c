/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2024/12/30 11:21:25 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			exit(printf("Error\nCan't open file\n"));
		}
		t_scene scene;
		ft_memset(&scene, 0, sizeof(t_scene));
		if (parse_cub(fd, &scene) == -1)
		{
			free_scene(&scene);
			exit(printf("Error\nInvalid file\n"));
		}
		else
		{
			for (size_t i = 0; i < scene.map_height; i++)
			{
				ft_putstr_fd(scene.map[i], 1);
				ft_putstr_fd("\n", 1);
			}
		}
		free_scene(&scene);
	}
	else
		exit(printf("Error\nInvalid number of arguments\n"));
	return (0);
}
