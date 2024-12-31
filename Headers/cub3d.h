/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:56:12 by abamksa           #+#    #+#             */
/*   Updated: 2024/12/31 08:55:11 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "AnsiEscCodes.h"
# include <X11/keysym.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <X11/X.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# define BUFFER_SIZE 1024

typedef struct s_scene
{
	char *north;
	char *south;
	char *west;
	char *east;
	int floor[3];
	int ceiling[3];
	char **map;
	size_t map_width;
	size_t map_height;
} t_scene;

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_scene *scene;
} t_data;

int	get_next_line(int fd, char **str);
void print_error(char *error, char *file, int line);
void free_scene(t_scene *scene);
int	parse_cub(int fd, t_scene *scene);

#endif
