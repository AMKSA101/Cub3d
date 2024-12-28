/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:56:12 by abamksa           #+#    #+#             */
/*   Updated: 2024/12/28 11:27:21 by abamksa          ###   ########.fr       */
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
	char **map;
	int floar[3];
	int ceiling[3];
	int map_width;
	int map_height;
} t_scene;

#endif
