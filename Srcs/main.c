/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2024/12/28 11:46:14 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	get_next_line(int fd, char **str)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	size_t total_size = 0;
	*str = NULL;

	// Reads the file content
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
		char *new_content = (char *)realloc(*str, total_size + bytes_read + 1);
		if (!new_content)
		{
			free(*str);
			close(fd);
			perror("Error reallocating memory");
			return -1;
		}
		*str = new_content;
		memcpy(*str + total_size, buffer, bytes_read);
		total_size += bytes_read;
	}
	if (bytes_read == -1) {
		free(*str);
		close(fd);
		perror("Error reading file");
		return -1;
	}
	if (*str)
		(*str)[total_size] = '\0';
	return total_size;
}

int	parse_cub(int fd, t_scene *scene)
{
	char *line;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "NO", 3))
		{
			scene->north = ft_strdup(line + 3);
		}
		else if (ft_strncmp(line, "SO", 3))
		{
			scene->south = ft_strdup(line + 3);
		}
		else if (ft_strncmp(line, "WE", 3))
		{
			scene->west = ft_strdup(line + 3);
		}
		else if (ft_strncmp(line, "EA", 3))
		{
			scene->east = ft_strdup(line + 3);
		}
		else if (ft_strncmp(line, "F", 2))
		{
			char **split = ft_split(line + 2, ',');
			scene->floar[0] = ft_atoi(split[0]);
			scene->floar[1] = ft_atoi(split[1]);
			scene->floar[2] = ft_atoi(split[2]);
			free(split);
		}
		else if (ft_strncmp(line, "C", 2))
		{
			char **split = ft_split(line + 2, ',');
			scene->ceiling[0] = ft_atoi(split[0]);
			scene->ceiling[1] = ft_atoi(split[1]);
			scene->ceiling[2] = ft_atoi(split[2]);
			free(split);
		}
		else if (ft_strncmp(line, "1", 1))
		{
			scene->map = ft_split(line, '\n');
			scene->map_height = 0;
			scene->map_width = 0;
			while (scene->map[scene->map_height])
			{
				int row_length = ft_strlen(scene->map[scene->map_height]);
				if (row_length > scene->map_width)
					scene->map_width = row_length;
				scene->map_height++;
			}
		}
		else
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("Error\nCan't open file\n", 2);
			return (1);
		}
		t_scene scene;
		if (parse_cub(fd, &scene) == -1)
		{
			ft_putstr_fd("Error\nInvalid file\n", 2);
			return (1);
		}
		
	}
	else
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	return (0);
}
