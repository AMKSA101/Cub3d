/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:42:18 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 18:41:02 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	print_error(char *error, char *file, int line)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(RESET, 2);
}

void	free_scene(t_scene *scene)
{
	if (scene == NULL)
		return ;
	if (scene->north_texture)
		free(scene->north_texture);
	if (scene->south_texture)
		free(scene->south_texture);
	if (scene->east_texture)
		free(scene->east_texture);
	if (scene->west_texture)
		free(scene->west_texture);
	if (scene->map)
		double_free(scene->map);
}

int	check_file_extension(char *file_name, char *ext)
{
	size_t	len;
	size_t	size;

	len = ft_strlen(file_name);
	size = ft_strlen(ext);
	if (len < 4 || ft_strncmp(file_name + len - size, ext, size) != 0)
		return (-1);
	return (0);
}

void	double_free(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_alloc(char ***arr, int size)
{
	int	i;

	i = 0;
	*arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!*arr)
	{
		print_error(strerror(errno), __FILE__, __LINE__);
		return (-1);
	}
	while (i < size)
	{
		(*arr)[i] = NULL;
		i++;
	}
	(*arr)[i] = NULL;
	return (0);
}
