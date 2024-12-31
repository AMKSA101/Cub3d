/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2024/12/31 12:15:48 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	ft_parse(char *file_name, t_data *data);
int	check_file_extension(char *file_name);
int	parse_cube(int fd, int line_count, t_scene *scene);
int	count_lines(char *file_name);

int	main(int ac, char **av)
{
	t_data data;
	t_scene scene;

	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&scene, 0, sizeof(t_scene));
	data.scene = &scene;
	if (ac == 2)
	{
		if (ft_parse(av[1], &data) == -1)
			return(-1);
		else
		{
			for (size_t i = 0; i < scene.map_height; i++)
			{
				ft_putstr_fd(scene.map[i], 1);
				ft_putstr_fd("\n", 1);
			}
		}
		// free_scene(scene);
	}
	else
		return(print_error("Invalid arguments", __FILE__, __LINE__), -1);
	return (0);
}

int	ft_parse(char *file_name, t_data *data)
{
	t_scene *scene __attribute_maybe_unused__;
	int line_count;

	scene = data->scene;
	if (check_file_extension(file_name) == -1)
		return (-1);

	line_count = count_lines(file_name);
	if (line_count == -1)
		return (-1);
	int fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(print_error(strerror(errno), __FILE__, __LINE__), -1);
	parse_cube(fd, line_count, scene);
	return (0);
}

int	count_lines(char *file_name)
{
	int fd;
	int line_count;
	char *line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(print_error(strerror(errno), __FILE__, __LINE__), -1);
	line_count = 0;
	while ((get_next_line(fd, &line)) >= 0)
	{
		if (line[0] == '\0')
			continue;
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}

int	parse_cube(int fd, int line_count, t_scene *scene __attribute_maybe_unused__)
{
	char **content;
	char *line;
	int i;

	content = (char **)malloc(sizeof(char *) * line_count);
	if (!content)
		return(print_error(strerror(errno), __FILE__, __LINE__), -1);
	content[line_count] = NULL;
	line = NULL;
	i = 0;
	while ((get_next_line(fd, &line)) >= 0)
	{
		if (line[0] == '\0')
			continue;
		content[i++] = ft_strdup(line);
		free(line);
	}
	close(fd);
	for (int j = 0; j < line_count; j++)
		printf("%s\n", content[j]);
	return (0);
}
int	check_file_extension(char *file_name)
{
	size_t len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp(file_name + len - 4, ".cub", 4) != 0)
		return(print_error("Invalid file extension", __FILE__, __LINE__), -1);
	return (0);
}
