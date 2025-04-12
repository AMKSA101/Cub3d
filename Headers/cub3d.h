/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:56:12 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 10:41:24 by abamksa          ###   ########.fr       */
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
# define PI 3.14159265359
# define RIGHT 65361
# define LEFT 65363
# define HEIGHT 800
# define WIDTH 1080
# define BLOCK 30
# define W 119
# define S 115
# define D 100
# define A 97

typedef enum e_wall
{
	NONE,
	NORTH,
	SOUTH,
	WEST,
	EAST
} t_wall;

typedef struct s_texture
{
	void	*north;
	int		north_width;
	int		north_height;
	void	*south;
	int		south_width;
	int		south_height;
	void	*west;
	int		west_width;
	int		west_height;
	void	*east;
	int		east_width;
	int		east_height;
	void *texture_;
	int 	tex_width;
	int		tex_height;
	char	*texture_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	float	new_y;
	float	new_x;
	double	dir_x;
	double	dir_y;
	float	speed;
	double	angle;
	float	cos_angle;
	float	sin_angle;
	bool	key_up;
	bool	key_left;
	bool	key_down;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
	bool	speed_rotate;
} t_player;

typedef struct s_scene
{
	char *north;
	char *south;
	char *west;
	char *east;
	int floor[3];
	int	ceiling[3];
	char	**map;
	int		map_x;
	int		map_y;
	size_t map_width;
	size_t map_height;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
	double	player_start_x;
	double	player_start_y;
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	int floor_color;
	int		ceiling_color;
	char	*data;

	int side;

	char player_start_dir;
} t_scene;


typedef struct s_ray
{
	float	ray_x;
	float	ray_y;
	float	step;
	float	dist;
	float	height;
	int		start_y;
	int		end_y;
	double	side_dist_x;
	double side_dist_y;
	float	ray_dir_x;
	float	ray_dir_y;

	double	delta_dist_x;
	double	delta_dist_y;
	double perp_wall_dist;

	double distance;
	int		step_x;
	int		step_y;
	int hit_x;
	int hit_y;
	int side;
	double wall_x;
	t_wall wall;
} t_ray;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	void	*img;
} t_mlx;

typedef struct s_data
{
	t_mlx		*mlx;
	t_player	*player;
	t_ray		*ray;
	t_scene		*scene;
	t_texture *texture;
} t_data;

/*draw.c*/
void	get_wall_height(t_data *data, float start_x, int i);
int		draw_loop(t_data *data);
void	draw_wall(t_data *data, float start_x, int i);
void	draw_pixel(t_data *data, int x, int y, int size, int color);
void	draw_map(t_data *data);
/*------*/

/*init.c*/
void	init_game(t_data *data);
void	init_player_position(t_player *player, t_scene *img);
void	init_player(t_player *player, t_scene *img);
/*------*/


/*move.c*/
int		key_pres(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	move_player(t_scene *img, t_player *player);
void	direction_of_player(t_scene *img, t_player *player);
int		destroynotify(t_data *data);
/*------*/

/*utils*/
int		is_wall(t_scene *img, float x, float y);
void	clear_image(t_data *data);
float	distance(float x, float y);
void	get_start_x(t_data *data, t_player *player, t_mlx *mlx, t_scene *scene);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
/*-----*/

void	double_free(char **arr);
void	free_scene(t_scene *scene);
void	free_scene(t_scene *scene);
int		ft_alloc(char ***arr, int size);
int		get_next_line(int fd, char **str);
void	print_error(char *error, char *file, int line);
int		check_file_extension(char *file_name, char *ext);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~parsing~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int	allocate_components(char ***texture, char ***color, char ***map, int size, int map_start);
int	extract_textures_and_colors(char **content, int map_start, char **texture, char **color);
int	check_file_input(char **content, int size, t_data *data, t_scene *scene);
int	parse_cube(int fd, int line_count, t_data *data, t_scene *scene);
int	copy_map_data(char **content, int map_start, int size, char **map);
int	find_map_start(char **content, int size);
int	ft_parse(char *file_name, t_data *data);
int	calculate_map_width(t_scene *scene);
int	count_lines(char *file_name);
int	check_empty_line(char *line);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~map parsing~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int	check_line(char *line);
int	check_map_line(char *line);
int	parse_map(char **map, t_scene *scene);
int	check_borders(char **map, t_scene *scene);
int	check_map_valid(char **map, t_scene *scene);
int is_valid_zero(char **map, size_t i, size_t j, t_scene *scene);
int is_wall_or_player(char c);
int is_player(char c);
int es_wall(char c);
int is_space(char c);
int process_map_line(char **map, size_t i, size_t *player_count, t_scene *scene);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~texture parsing~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int	parse_texture(char **texture, t_data *data, t_scene *scene);
int	parse_texture_line(char *line, t_scene *scene);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~color parsing~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int	parse_rgb_values(char *str, int *r, int *g, int *b);
int	parse_color_line(char *line, t_scene *scene);
int	parse_color(char ** color, t_scene *scene);
int	parse_color(char **color, t_scene *scene);
int	check_separator(char *str, char c);
#endif
