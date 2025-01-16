/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:56:12 by abamksa           #+#    #+#             */
/*   Updated: 2025/01/16 15:58:02 by abamksa          ###   ########.fr       */
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
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	int floor_color;
	int ceiling_color;
	char **map;
	size_t map_width;
	size_t map_height;
	char player_start_dir;
	double player_start_x;
	double player_start_y;
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

void	double_free(char **arr);
void	free_scene(t_scene *scene);
void	free_scene(t_scene *scene);
int		ft_alloc(char ***arr, int size);
int		get_next_line(int fd, char **str);
void	print_error(char *error, char *file, int line);
int		check_file_extension(char *file_name, char *ext);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~parsing~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int	check_file_input(char **content, int size, t_scene *scene);
int	parse_cube(int fd, int line_count, t_scene *scene);
int	ft_parse(char *file_name, t_data *data);
int	count_lines(char *file_name);
int	check_empty_line(char *line);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~map parsing~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int	check_line(char *line);
int	check_map_line(char *line);
int	parse_map(char **map, t_scene *scene);
int	check_borders(char **map, t_scene *scene);
int	check_map_valid(char **map, t_scene *scene);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~texture parsing~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int	parse_texture(char **texture, t_scene *scene);
int	parse_texture_line(char *line, t_scene *scene);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~color parsing~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int	parse_rgb_values(char *str, int *r, int *g, int *b);
int	parse_color_line(char *line, t_scene *scene);
int	parse_color(char ** color, t_scene *scene);
int	parse_color(char **color, t_scene *scene);
int	check_separator(char *str, char c);
#endif
